/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:27:42 by rmount            #+#    #+#             */
/*   Updated: 2023/07/16 10:21:51 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_dinner    dinner;

    if (ac < 5 || ac > 6)
    {
        err_mess(NUM_ARGS);
    }
    is_valid_input(ac, av);
    init_dinner(&dinner, av);
    dinner.start_time = get_current_time();
    create_thread(&dinner);
    destroy_and_exit(&dinner);
}