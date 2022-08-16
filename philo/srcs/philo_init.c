/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/16 17:00:48 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_params(t_main *m, int ac, char **av)
{
	m->i = 1;
	m->ret = 1;
	while (m->ret == 1 && m->i < ac)
	{
		m->j = 0;
		while (av[m->i][m->j])
		{
			if (!ft_isdigit(av[m->i][m->j]))
				m->ret = ft_error(ERR_DIGITS);
			m->j++;
		}
		m->data = ft_atoli(av[m->i]);
		if (m->i == 1)
		{
			if (m->data > MAX_THREADS || m->data == 0)
				m->ret = ft_error(ERR_ALLOC);
		}
		else if (m->data < INT_MIN || m->data > INT_MAX || m->data == 0)
			m->ret = ft_error(ERR_VAL);
		m->i++;
	}
	return (m->ret);
}

int	main_alloc(t_main *m, int ac, char **av)
{	
	m->philo_nb = (int)ft_atoli(av[1]);
	m->philosophers = (pthread_t *)malloc(sizeof(pthread_t)
			* (long unsigned)m->philo_nb);
	if (!m->philosophers)
		return (0);
	m->err = (int *)malloc(sizeof(int) * (long unsigned)m->philo_nb);
	if (!m->err)
		return (0);
	m->platter = (int *)malloc(sizeof(int) * (long unsigned)m->philo_nb);
	if (!m->platter)
		return (0);
	m->bigbang = (unsigned int *)malloc(sizeof(unsigned int)
			* (long unsigned)m->philo_nb);
	if (!m->bigbang)
		return (0);
	m->expected_death = (unsigned int *)malloc(sizeof(unsigned int)
			* (long unsigned)m->philo_nb);
	if (!m->expected_death)
		return (0);
	if (ac == 6)
	{
		m->stock_limit = 1;
		m->done_eating = m->philo_nb;
	}
	return (1);
}

int	philos_alloc(t_main *m, int ac, char **av)
{	
	memset(m->platter, 0, (long unsigned)m->philo_nb);
	m->p = (t_philos *)malloc(sizeof(t_philos) * (long unsigned)m->philo_nb);
	if (!m->p)
		return (0);
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		m->p[m->i] = (t_philos){0};
		m->p[m->i].philo_id = m->i + 1;
		m->p[m->i].l_fork = m->i;
		m->p[m->i].r_fork = (m->i + 1) % m->philo_nb;
		m->p[m->i].time2_die = (unsigned)ft_atoli(av[2]);
		m->p[m->i].time2_eat = (unsigned)ft_atoli(av[3]);
		m->p[m->i].time2_sleep = (unsigned)ft_atoli(av[4]);
		m->p[m->i].time2_think = m->p[m->i].time2_eat;
		m->p[m->i].m = m;
		if (ac == 6)
			m->p[m->i].eat_counter = (int)ft_atoli(av[5]);
		m->i++;
	}
	return (1);
}

int	mutex_init(t_main *m)
{
	m->mt.waiter = malloc(sizeof(pthread_mutex_t) * (long unsigned)m->philo_nb);
	if (!m->mt.waiter)
		return (0);
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (pthread_mutex_init(&m->mt.waiter[m->i], NULL) != 0)
			return (0);
		m->i++;
	}
	if (pthread_mutex_init(&m->mt.time, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&m->mt.display, NULL) != 0)
		return (0);
	return (1);
}

int	init_params(t_main *m, int ac, char **av)
{	
	if (!check_params(m, ac, av))
		return (0);
	if (!main_alloc(m, ac, av))
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
