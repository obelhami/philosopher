#include "philo.h"

void error(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

// void    ft_init_table(t_table *table) {
//     if(table) {
//         table->end_simmulation = 0;
//         table->forks = NULL;
//         table->nbr_limit_meals = 0;
//         table->nbr_philosophers = 0;
//         table->philos = NULL;
//         table->start_simmulation = 0;
//         table->time_to_die = 0;
//         table->time_to_eat = 0;
//         table->time_to_sleep = 0;
//     }
// }

void    ft_print_table(t_table table) 
{
        printf("table.nbr_limit_meals = |%ld|\n", table.nbr_limit_meals);
        printf("table.nbr_philosophers = |%ld|\n", table.nbr_philosophers);
        printf("table.time_to_die = |%ld|\n", table.time_to_die);
        printf("table.time_to_eat = |%ld|\n", table.time_to_eat);
        printf("table.time_to_sleep = |%ld|\n", table.time_to_sleep);
}

void    eat(t_philo *philosopher)
{
    printf("Philosopher %d is eating\n", philosopher->id);
    // usleep(philosopher->table->time_to_eat * 1000);
    printf("Philosopher %d has finished eating\n", philosopher->id);
}

void    *routine(void *philo)
{
    t_philo *philosopher;
    philosopher = (t_philo *)philo;
    while (1)
    {
    printf("philosopher->id = |%d|\n", philosopher->id);
        // eat(philosopher);
        // usleep(philosopher->table->time_to_sleep * 1000);
        // printf("philosopher->table->time_to_sleep = |%ld|\n", philosopher->table->time_to_sleep);
    }
    return NULL;
}

void    data_init(t_table *table)
{
    pthread_t *threads;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * table->nbr_philosophers);
    if (!threads)
        error("Error: malloc failed");
    table->philos = malloc(sizeof(t_philo) * table->nbr_philosophers);
    if (!table->philos)
        error("Error: malloc failed");
    while (i < table->nbr_philosophers)
    {
        table->philos[i].id = i + 1;
        if (pthread_create(&threads[i], NULL, &routine, &table->philos[i]))
            error("Error: pthread_create failed");
        i++;
    }
    i = 0;
    while (i < table->nbr_philosophers)
    {
        if (pthread_join(threads[i], NULL))
            error("Error: pthread_join failed");
        i++;
    }
    free(threads);
}

int main(int argc, char **argv)
{
    t_table table;

    // ft_init_table(&table);
    if (argc != 5 && argc != 6)
        error("Invalid number of arguments");
    else
    {
        memset(&table, 0, sizeof(t_table));
        parsing(argc, argv, &table);
        ft_print_table(table);
        data_init(&table);
    }
    return 0;
}
