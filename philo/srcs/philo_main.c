/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:24:36 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/08 22:07:08 by seozcan          ###   ########.fr       */
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

int	philosophers_init(t_main *m)
{
	unsigned int	i;

	i = 0;
	while (i < m->philo_nb)
	{
		m->p[i].philo_id = i + 1;
		m->err[i] = pthread_create(&m->philosophers[i], NULL,
				&routine, &m->p[i]);
		if (m->err[i] != 0)
		{
			ft_error(ERR_THREAD);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philosophers_join(t_main *m)
{
	unsigned int	i;

	i = 0;
	while (i < m->philo_nb)
	{
		if (pthread_join(m->philosophers[i],
				(void *)(intptr_t)m->err[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_flush(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		pthread_mutex_destroy(&m->mt.forks[m->i]);
		m->i++;
	}
	pthread_mutex_destroy(&m->mt.sleep);
	pthread_mutex_destroy(&m->mt.think);
	pthread_mutex_destroy(&m->mt.print_dead);
	pthread_mutex_destroy(&m->mt.print_sleep);
	pthread_mutex_destroy(&m->mt.print_fork);
	pthread_mutex_destroy(&m->mt.print_eat);
	pthread_mutex_destroy(&m->mt.print_think);
	free(m->mt.forks);
	free(m->p);
	free(m->philosophers);
	free(m->err);
}

int	main(int ac, char **av)
{
	t_main	m;

	m = (t_main){0};
	m.mt = (t_mutex){0};
	m.t = (t_time){0};
	if (ac < 5 || ac > 6)
	{
		ft_error(ERR_ARGS);
		return (0);
	}
	if (!init_params(&m, ac, av))
		return (0);
	if (!philosophers_init(&m))
		return (0);
	if (!philosophers_join(&m))
		return (0);
	ft_flush(&m);
	return (0);
}
