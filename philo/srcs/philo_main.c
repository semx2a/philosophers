/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:24:36 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/10 14:46:18 by seozcan          ###   ########.fr       */
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

void	ft_flush(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		pthread_mutex_destroy(&m->mt.waiter[m->i]);
		pthread_mutex_destroy(&m->mt.time[m->i]);
		m->i++;
	}
	pthread_mutex_destroy(&m->mt.satiated);
	pthread_mutex_destroy(&m->mt.display);
	pthread_mutex_destroy(&m->mt.reaper);
	pthread_mutex_destroy(&m->mt.chrono);
	free(m->mt.waiter);
	free(m->p);
	free(m->philosophers);
	free(m->err);
}

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
	if (init_params(&m, ac, av))
	{
		if (!philosophers_init(&m))
			ft_error(ERR);
		ecg(&m);
		if (!philosophers_join(&m))
			ft_error(ERR);
	}
	ft_flush(&m);
	return (0);
}
