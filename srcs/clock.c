/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:21:21 by rmount            #+#    #+#             */
/*   Updated: 2023/07/16 12:39:40 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_current_time(void)
{
    struct timeval  current_time;

    gettimeofday(&current_time, NULL);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void    take_nap(long long time_to_sleep)
{
    long long time_end;

    time_end = (get_current_time() * 1000) + time_to_sleep;
    while ((get_current_time() * 1000) <= time_end)
    {
        usleep(100);
    }
}