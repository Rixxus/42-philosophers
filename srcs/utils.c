/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:00:32 by rmount            #+#    #+#             */
/*   Updated: 2023/07/14 16:27:30 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		err_mess(char *message)
{
	printf("Error: %s\n", message);
	exit(1);
}

int 	ft_atoi(char *str)
{
	unsigned long long int	num;
	int						i;

	num = 0;
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
	{
		err_mess(ARG_INVALID);
	}
	return ((int)num);
}

int		ft_is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int		is_valid_input(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (ft_is_number(av[i]) == 0)
		{
			err_mess(ARG_INVALID);
		}
		i++;
	}
	return (1);
}

void	destroy_and_exit(t_deets *deets)
{
	int i;

	i = 0;
	while (i < deets->number_of_philosophers)
	{
		pthread_mutex_destroy(&deets->philo[i].fork);
		i++;
	}
	pthread_mutex_destroy(&deets->action);
	free(deets->philo);
	exit(0);
}

	