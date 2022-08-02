/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/02 19:46:41 by seozcan          ###   ########.fr       */
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
	m->philo_nb = ft_atoi(av[1]);
	if (m->philo_nb > MAX_THREADS)
		return (0);
	m->philosophers = (pthread_t *)malloc(sizeof(pthread_t)
			* (long unsigned)m->philo_nb);
	if (!m->philosophers)
		return (0);
	m->err = (int *)malloc(sizeof(int) * (long unsigned)m->philo_nb);
	return (1);
}

int	philos_alloc(t_main *m, int ac, char **av)
{	
	m->p = malloc(sizeof(t_philos) * (long unsigned)m->philo_nb);
	if (!m->p)
		return (0);
	while (m->i < m->philo_nb)
	{
		m->p[m->i] = (t_philos){0};
		m->p[m->i].l_fork = m->i;
		m->p[m->i].r_fork = m->i + 1;
		m->p[m->i].time2_die = (unsigned)ft_atoi(av[2]);
		m->p[m->i].expected_death = m->p[m->i].time2_die;
		m->p[m->i].time2_eat = (unsigned)ft_atoi(av[3]) * 1000;
		m->p[m->i].time2_sleep = (unsigned)ft_atoi(av[4]) * 1000;
		if (ac == 6)
		{
			m->p[m->i].n_eats = ft_atoi(av[5]);
			if (m->p[m->i].n_eats >= INT_MAX)
				return (0);
			m->p[m->i].food_limit = 1;
		}
		m->p[m->i].m = m;
		m->i++;
	}
	m->p[m->i - 1].l_fork = 0;
	m->p[m->i - 1].r_fork = m->i;
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
	return (1);
}
