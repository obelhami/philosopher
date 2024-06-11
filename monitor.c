/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelhami <obelhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:14:55 by obelhami          #+#    #+#             */
/*   Updated: 2024/06/11 05:42:18 by obelhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_table *table;
    long i;

    table = (t_table *)arg;
    while (true)
    {
        M_LOCK(&table->monitor_mutex);
        if (table->flag == 1)
        {
            M_UNLOCK(&table->monitor_mutex);
            break;
        }
        M_UNLOCK(&table->monitor_mutex);
    }

    while (true)
    {
        i = 0;
        while (i < table->nbr_philosophers)
        {
            M_LOCK(&table->meal_mutex);
            if (get_time() - table->philos[i].last_meal_time >= table->time_to_die)
            {
                if (message(&table->philos[i], "dead"))
                {
                    M_UNLOCK(&table->meal_mutex);
                    return (NULL);
                }
                M_LOCK(&table->mutex);
                table->end_simmulation = true;
                M_UNLOCK(&table->mutex);
            }
            M_UNLOCK(&table->meal_mutex);
            i++;
        }        
    }
    // return (NULL);
}
