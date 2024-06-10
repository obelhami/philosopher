/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelhami <obelhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:00:01 by obelhami          #+#    #+#             */
/*   Updated: 2024/06/10 05:51:19 by obelhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_philos(t_table *table)
{
    long i;

    i = 0;
    while (i <  table->nbr_philosophers)
    {
        if (M_INIT(&table->forks[i], NULL))
            return (1);
        i++;
    }
    i = 0;
    while (i < table->nbr_philosophers)
    {
        table->philos[i].id = i + 1;
        table->philos[i].table = table;
        table->philos[i].full = false;
        table->philos[i].meals_counter = 0; 
        i++;
    }
    return (0);
}
int assign_forks(t_table *table)
{
    long i;
    int nbr_philos;
 
    nbr_philos = table->nbr_philosophers;
    i = 0;
    while (i < table->nbr_philosophers)
    {
        if (i  == 0)
        {
            table->philos[i].right_fork = &table->forks[nbr_philos - 1];
            table->philos[i].left_fork = &table->forks[i];
        }
        else
        {
            table->philos[i].right_fork = &table->forks[i - 1];
            table->philos[i].left_fork = &table->forks[i]; 
        }
        i++;
    }
    return (0);
}

int    data_init(t_table *table)
{
    long i;

    //TODO create monitor thread
    if (M_INIT(&table->mutex, NULL))
        return (1);
    i = 0;
    table->philos = malloc(sizeof(t_philo) * table->nbr_philosophers);
    if (!table->philos)
        return(1);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philosophers);
    if (!table->forks)
        return(1);
    init_philos(table);
    assign_forks(table);
    table->start_simmulation = get_time();
    while (i < table->nbr_philosophers)
    {
        if (pthread_create(&table->philos[i].th, NULL, &routine, &table->philos[i]))
            return (1);
        i++;
    }
    i = 0;
    while (i < table->nbr_philosophers)
    {
        if (pthread_join(table->philos[i].th, NULL))
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_table table;

    if (argc != 5 && argc != 6)
    {
        printf("Error: Invalid number of arguments\n");
        return (1); 
    }
    else
    {
        memset(&table, 0, sizeof(t_table));
        if (parsing(argc, argv, &table))
            return (1);
        // ft_print_table(table);
        if (data_init(&table))
            return (1);
    }
    return 0;
}
