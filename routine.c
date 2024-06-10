/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelhami <obelhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:32:11 by obelhami          #+#    #+#             */
/*   Updated: 2024/06/10 06:56:37 by obelhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int message(t_philo *philo, char *msg)
{
    M_LOCK(&philo->table->mutex);
    if (philo->table->end_simmulation == true)
    {
        M_UNLOCK(&philo->table->mutex);
        return (1);
    }
    printf("%ld\t\t%d\t\t%s\n", get_time()- philo->table->start_simmulation, philo->id,  msg);
    M_UNLOCK(&philo->table->mutex);
    return (0);
}


int think(t_philo *philo)
{
    if (message(philo, "is thinking"))
        return (1);
    return (0);
}

int eat(t_philo *philo)
{
    if (philo->table->nbr_limit_meals != -1 &&  philo->meals_counter >= philo->table->nbr_limit_meals)
        return (1);
    M_LOCK(philo->right_fork);
    if (message(philo, "has taken right fork"))
    {
        M_UNLOCK(philo->right_fork);
        return (1);
    }
    M_LOCK(philo->left_fork);
    if (message(philo, "has taken left fork"))
    {
        M_UNLOCK(philo->left_fork);
        return (1);
    }
    if (message(philo, "is eating"))
        return (1);
    philo->meals_counter++;
    ft_sleep(philo->table->time_to_eat);
    M_LOCK(&philo->table->mutex);
    philo->last_meal_time = get_time();
    M_UNLOCK(&philo->table->mutex);
    M_UNLOCK(philo->right_fork);
    M_UNLOCK(philo->left_fork);
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
    
    while (1)
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

