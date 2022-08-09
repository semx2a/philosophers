/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/09 23:27:09 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_params(t_main *m, int ac, char **av)
{
	m->i = 1;
	while (m->i < ac)
	{
		m->j = 0;
		while (av[m->i][m->j])
		{
			if (!ft_isdigit(av[m->i][m->j]))
				return (0);
			m->j++;
		}
		m->i++;
	}
	m->i = 1;
	while (m->i < ac)
	{
		m->data = ft_atoli(av[m->i]);
		if (m->data < INT_MIN || m->data > INT_MAX)
			return (0);
		m->i++;
	}
	return (1);
}

int	main_alloc(t_main *m, char **av)
{	
	m->philo_nb = (int)ft_atoli(av[1]);
	if (m->philo_nb > MAX_THREADS)
		return (0);
	m->philosophers = (pthread_t *)malloc(sizeof(pthread_t)
			* (long unsigned)m->philo_nb);
	if (!m->philosophers)
		return (0);
	m->err = (int *)malloc(sizeof(int) * (long unsigned)m->philo_nb);
	if (!m->err)
		return (0);
	m->p = (t_philos *)malloc(sizeof(t_philos) * (long unsigned)m->philo_nb);
	if (!m->p)
		return (0);
	return (1);
}

int	philos_alloc(t_main *m, int ac, char **av)
{	
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		m->p[m->i] = (t_philos){0};
		m->p[m->i].philo_id = m->i + 1;
		m->p[m->i].l_fork = m->i;
		m->p[m->i].r_fork = m->i + 1;
		if (m->i == m->philo_nb - 1)
			m->p[m->i].r_fork = 0;
		m->p[m->i].time2_die = (unsigned)ft_atoli(av[2]);
		m->p[m->i].expected_death = m->p[m->i].time2_die;
		m->p[m->i].time2_eat = (unsigned)ft_atoli(av[3]);
		m->p[m->i].time2_sleep = (unsigned)ft_atoli(av[4]);
		m->p[m->i].offset = m->p[m->i].time2_sleep / (unsigned int)m->philo_nb;
		if (ac == 6)
		{
			m->p[m->i].n_eats = (int)ft_atoli(av[5]);
			if (m->p[m->i].n_eats >= INT_MAX)
				return (0);
			m->p[m->i].food_limit = 1;
		}
		m->p[m->i].m = m;
		m->i++;
	}
	return (1);
}

int	mutex_init(t_main *m)
{
	m->mt.waiter = malloc(sizeof(pthread_mutex_t) * (long unsigned)m->philo_nb);
	if (!m->mt.waiter)
		return (0);
	m->mt.time = malloc(sizeof(pthread_mutex_t) * (long unsigned)m->philo_nb);
	if (!m->mt.time)
		return (0);
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (pthread_mutex_init(&m->mt.waiter[m->i], NULL) != 0)
			return (0);
		if (pthread_mutex_init(&m->mt.time[m->i], NULL) != 0)
			return (0);
		m->i++;
	}
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
	if (!check_params(m, ac, av))
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
	return (1);
}
