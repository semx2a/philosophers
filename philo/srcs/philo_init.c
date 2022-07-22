/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/22 21:10:01 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_params(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main_alloc(t_main *m, char **av)
{
	m->philo_nb = ft_atolu(av[1]);
	if (m->philo_nb > MAX_THREADS || m->philo_nb >= INT_MAX)
		return (0);
	m->philosophers = (pthread_t *)malloc(sizeof(pthread_t) * m->philo_nb);
	if (!m->philosophers)
		return (0);
	m->err = (int *)malloc(sizeof(int) * m->philo_nb);
	if (!m->err)
		return (0);
	return (1);
}

int	philos_alloc(t_main *m, int ac, char **av)
{
	m->p = malloc(sizeof(t_philos) * m->philo_nb);
	if (!m->p)
		return (0);
	while (m->i < m->philo_nb)
	{
		m->p[m->i] = (t_philos){0};
		m->p[m->i].l_fork = m->i ;
		m->p[m->i].r_fork = m->i + 1;
		if (m->i == m->philo_nb - 1)
			m->p[m->i].r_fork = 0;
		m->p[m->i].time2_die = (useconds_t)ft_atolu(av[2]);
		m->p[m->i].time2_eat = (useconds_t)ft_atolu(av[3]) * 1000;
		m->p[m->i].time2_sleep = (useconds_t)ft_atolu(av[4]) * 1000;
		if (ac == 6)
		{
			m->p[m->i].n_eats = ft_atolu(av[5]);
			m->p[m->i].food_limit = 1;
		}
		if (m->p[m->i].n_eats >= INT_MAX)
			return (0);
		m->p[m->i].m = m;
		m->i++;
	}
	return (1);
}

int	mutex_init(t_main *m)
{
	m->mt.waiter = malloc(sizeof(pthread_mutex_t) * m->philo_nb);
	if (!m->mt.waiter)
		return (0);
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (pthread_mutex_init(&m->mt.waiter[m->i], NULL) != 0)
			return (0);
		m->i++;
	}
	if (pthread_mutex_init(&m->mt.sleep, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&m->mt.think, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&m->mt.display, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&m->mt.satiated, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&m->mt.reaper, NULL) != 0)
		return (0);
	return (1);
}

int	init_params(t_main *m, int ac, char **av)
{	
	if (!check_params(ac, av))
	{
		ft_error(ERR_DIGITS);
		return (0);
	}
	if (!main_alloc(m, av))
	{
		ft_error(ERR_ALLOC);
		return (0);
	}
	if (!philos_alloc(m, ac, av))
	{
		ft_error(ERR_PHILOS);
		return (0);
	}
	if (!mutex_init(m))
	{
		ft_error(ERR_MUTEX);
		return (0);
	}
	gettimeofday(&m->t.start, NULL);
	return (1);
}
