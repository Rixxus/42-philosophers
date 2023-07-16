/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:39:13 by rmount            #+#    #+#             */
/*   Updated: 2023/07/16 13:17:00 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo(t_dinner *dinner)
{
    int i;

    i = 0;
    dinner->philo = malloc(sizeof(t_philo) * dinner->number_of_philosophers);
    if (!dinner->philo)
    {
        return (0);
    }
    while (i < dinner->number_of_philosophers)
    {
        dinner->philo[i].philo_id = i + 1;
        dinner->philo[i].times_eaten = 0;
        dinner->philo[i].dinner = dinner;
        pthread_mutex_init(&dinner->philo[i].fork, NULL);
        if ((i + 1) == dinner->number_of_philosophers)
        {
            dinner->philo[i].left = &dinner->philo[0];
        }
        else
        {
            dinner->philo[i].left = &dinner->philo[i + 1];
        }
        dinner->philo[i].dinner = dinner;
        i++;
    }
    return (1);
}

void init_dinner(t_dinner *dinner, char **av)
{
    memset(dinner, 0, sizeof(t_dinner));
    dinner->number_of_philosophers = ft_atoi(av[1]);
    dinner->time_to_die = ft_atoi(av[2]);
    dinner->time_to_eat = ft_atoi(av[3]);
    dinner->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
    {
        dinner->times_philosopher_must_eat = ft_atoi(av[5]);
    }
    else
    {
        dinner->times_philosopher_must_eat = INT_MAX;
    }
    dinner->stuffed = 0;
    dinner->starved = 0;
    if (init_philo(dinner) != 1)
    {
        err_mess(INIT_ERR);
    }
    pthread_mutex_init(&dinner->action, NULL);
    return ;
}

static void *lonely_diner(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork);
    write_log(philo->dinner, philo, FORK);
    take_nap(philo->dinner->time_to_die * 1000);
    pthread_mutex_unlock(&philo->fork);
    return (NULL);
}

void    *philo_do(void *dinner)
{
    t_philo *philo;

    philo = (t_philo *)dinner;
    if (philo->dinner->times_philosopher_must_eat == 0)
    {
        return (NULL);
    }
    if (philo->dinner->number_of_philosophers == 1)
    {
        return (lonely_diner(philo));
    }
    if (philo->philo_id % 2 == 0)
    {
        usleep(1000);
    }
    while (philo->dinner->starved != 1)
    {
        philo_actions(philo);
        if (philo->times_eaten >= philo->dinner->times_philosopher_must_eat)
        {
            philo->dinner->stuffed = 1;
        }
    }
    return (NULL);
}

int create_thread(t_dinner *dinner)
{
    int i;

    i = 0;
    while (i < dinner->number_of_philosophers)
    {
        if (pthread_create(&dinner->philo[i].thread_id, NULL,
            &philo_do, &dinner->philo[i]) != 0)
            {
                err_mess(INIT_ERR);
            }
        dinner->philo[i].last_ate = dinner->start_time;
        i++;
    }
    check_if_died(dinner);
    i = 0;
    while (i < dinner->number_of_philosophers)
    {
        if (pthread_join(dinner->philo[i].thread_id, NULL) != 0)
        {
            err_mess(INIT_ERR);
        }
        i++;
    }
    return (1);
}