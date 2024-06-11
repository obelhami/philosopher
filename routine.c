/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelhami <obelhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:32:11 by obelhami          #+#    #+#             */
/*   Updated: 2024/06/11 05:42:58 by obelhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int message(t_philo *philo, char *msg)
{
    M_LOCK(&philo->table->mutex);
    /*check if the simulation end or not. if true do nothing*/
    if (philo->table->end_simmulation == true)
    {
        M_UNLOCK(&philo->table->mutex);
        return (1);
    }
    printf("%ld\t\t%d\t\t%s\n", get_time()- philo->table->start_simmulation, philo->id,  msg);
    M_UNLOCK(&philo->table->mutex);
    return (0);
}


int eat(t_philo *philo)
{
    M_LOCK(&philo->table->c_mutex);
    if (philo->table->nbr_limit_meals != -1 && philo->meals_counter >= philo->table->nbr_limit_meals)
    {
        philo->full = true;
        return (1);
    }
    M_UNLOCK(&philo->table->c_mutex);
    /* right fork */
    if (M_LOCK(philo->right_fork))
        return (1);
    if (message(philo, "taken a right fork"))
    {
        M_UNLOCK(philo->right_fork);
        return (1);
    }
    /* left fork*/
    if (M_LOCK(philo->left_fork))
        return (1);
    if (message(philo, "taken a left fork"))
    {
        M_UNLOCK(philo->right_fork);
        M_UNLOCK(philo->left_fork);
        return (1);
    }

    if (message(philo, "eating"))
    {
        M_UNLOCK(philo->right_fork);
        M_UNLOCK(philo->left_fork);
        return (1);
    }

    ft_sleep(philo->table->time_to_eat);
    
    M_LOCK(&philo->table->meal_mutex);
    philo->last_meal_time = get_time();
    M_UNLOCK(&philo->table->meal_mutex);
    M_LOCK(&philo->table->c_mutex);
    philo->meals_counter = philo->meals_counter + 1;
    M_UNLOCK(&philo->table->c_mutex);
    if (M_UNLOCK(philo->right_fork))
        return (1);
    if (M_UNLOCK(philo->left_fork))
        return (1);
    
    return (0);
}

int think(t_philo *philo)
{
    if (message(philo, "is thinking"))
        return (1);
    return (0);
}


int _sleep(t_philo *philo)
{
    if (message(philo, "is sleeping"))
        return (1);
    ft_sleep(philo->table->time_to_sleep);
    return (0);
}

void    *routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    M_LOCK(&philo->table->meal_mutex);
    philo->last_meal_time = get_time();
    M_UNLOCK(&philo->table->meal_mutex);
    while (true)
    {

        if (think(philo))
            break;
        if (eat(philo))
            break;
        if (_sleep(philo))
            break;
    }    
    return (NULL);
}

