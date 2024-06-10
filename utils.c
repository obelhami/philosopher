/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelhami <obelhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 03:08:58 by obelhami          #+#    #+#             */
/*   Updated: 2024/06/10 05:26:00 by obelhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
long get_time()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000 ) + (tv.tv_usec / 1000));
}

void  ft_sleep(long time)
{
    long current_time;

    current_time = get_time();
    while (get_time() - current_time < time);
}
