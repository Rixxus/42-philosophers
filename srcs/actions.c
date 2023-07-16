/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:32:56 by rmount            #+#    #+#             */
/*   Updated: 2023/07/16 13:19:44 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_actions(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	write_log(philo->dinner, philo, FORK);
	pthread_mutex_lock(&philo->left->fork);
	write_log(philo->dinner, philo, FORK);
	philo->last_ate = get_current_time();
	write_log(philo->dinner, philo, EAT);
	take_nap(philo->dinner->time_to_eat * 1000);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
	write_log(philo->dinner, philo, SLEEP);
	take_nap(philo->dinner->time_to_sleep * 1000);
	write_log(philo->dinner, philo, THINK);
}

void    write_log(t_dinner *dinner, t_philo *philo, char action)
{
	int run_time;

	run_time = (get_current_time() - dinner->start_time);
	pthread_mutex_lock(&dinner->action);
	if (dinner->stuffed != 1)
	{
		if (action == FORK)
			printf("%i %d has taken a fork\n", run_time, philo->philo_id);
		if (action == EAT)
			printf("%i %d is eating\n", run_time, philo->philo_id);
		if (action == SLEEP)
			printf("%i %d is sleeping\n", run_time, philo->philo_id);
		if (action == THINK)
			printf("%i %d is thinking\n", run_time, philo->philo_id);
		if (action == DIED)
			printf("%i %d died\n", run_time, philo->philo_id);
	}
	pthread_mutex_unlock(&dinner->action);
}

void	check_if_died(t_dinner *dinner)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < dinner->number_of_philosophers)
		{
			if (get_current_time() - dinner->philo->last_ate >= dinner->time_to_die)
			{
				dinner->starved = 1;
				write_log(dinner, dinner->philo, DIED);
				destroy_and_exit(dinner);
			}
			else if (dinner->stuffed == 1)
			{
				destroy_and_exit(dinner);
			}
			i++;
		}
	}
}