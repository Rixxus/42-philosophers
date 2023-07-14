/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:15:00 by rmount            #+#    #+#             */
/*   Updated: 2023/07/14 16:13:03 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define FORK 1
#define EAT 2
#define SLEEP 3
#define THINK 4
#define DIED 5

#define NUM_ARGS "Check number of arguments."
#define INIT_ERR "Initialisation failed."
#define ARG_INVALID "Argument is invalid - must be an int from \
0 to 2147483647 inclusive."

typedef struct s_deets t_deets;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				last_ate;
	int				times_eaten;
	pthread_mutex_t	fork;
	struct s_philo	*left;
	t_deets			*deets;
}	t_philo;

typedef struct s_deets
{
	int				number_of_philosophers;
	int	            time_to_die;
	int				time_to_sleep;
	int 			time_to_eat;
	int 			times_philosopher_must_sleep;
	int 			start_time;
	int 			all_eaten;
	int 			died;
	pthread_mutex_t action;
	t_philo			*philo;
}	t_deets;

int		get_current_time(void);
void	ft_usleep(long long time_to_sleep);
int		ft_atoi(char *str);
int		check_int(char *av);
int		ft_is_number(char *str);
int		is_valid_input(int ac, char **av);
int		err_mess(char *message);
int		init_philo(t_deets *deets);
int		init_deets(t_deets *deets, char **av);
void	destroy_and_exit(t_deets *deets);
void	philo_activity(t_philo *philo);
void	write_log(t_deets *deets, t_philo *philo, char activity);
int		create_philo_thread(t_deets *deets);
void	check_if_died(t_deets *deets);

#endif