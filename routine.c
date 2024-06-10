/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelhami <obelhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:32:11 by obelhami          #+#    #+#             */
/*   Updated: 2024/06/10 05:44:41 by obelhami         ###   ########.fr       */
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
    if (message(philo, "is eating"))
        return (1);
    ft_sleep(philo->table->time_to_eat);
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

