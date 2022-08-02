/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:24:36 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/02 19:46:17 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		PHILOSOPHERS

		ARGS:
		av[1]		number_of_philosophers
		av[2]		time_to_die 
		av[3]		time_to_eat
		av[4]		time_to_sleep
		av[5] 		[optional] number_of_times_each_philosopher_must_eat
*/

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_main	m;

	m = (t_main){0};
	m.mt = (t_mutex){0};
	if (ac < 5 || ac > 6)
	{
		ft_error(ERR_ARGS);
		return (0);
	}
	if (!init_params(&m, ac, av))
		return (0);
	if (!philosophers_init(&m))
		ft_error(ERR);
	if (!philosophers_join(&m))
		return (0);
	ft_flush(&m);
	return (0);
}
