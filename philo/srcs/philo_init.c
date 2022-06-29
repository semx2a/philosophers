/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/28 13:20:27 by seozcan          ###   ########.fr       */
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

int	params_alloc(t_main *m, int ac, char **av)
{	
	m->p.philo_nb = ft_atolu(av[1]);
	if (m->p.philo_nb > MAX_THREADS)
		return (0);
	m->p.philosophers = (pthread_t *)malloc(sizeof(pthread_t) * m->p.philo_nb);
	if (!m->p.philosophers)
		return (0);
	m->ret = (int *)malloc(sizeof(int) * m->p.philo_nb);
	if (!m->ret)
		return (0);
	if (m->p.philo_nb != 1 && m->p.philo_nb % 1 == 0)
		m->p.forks = m->p.philo_nb - 1;
	else
		m->p.forks = m->p.philo_nb;
	m->p.time_2die = ft_atolu(av[2]);
	m->t.time2_d = (useconds_t)m->p.time_2die * 1000;
	m->p.time_2eat = ft_atolu(av[3]);
	m->t.time2_e = (useconds_t)m->p.time_2eat * 1000;
	m->p.time_2sleep = ft_atolu(av[4]);
	m->t.time2_s = (useconds_t)m->p.time_2sleep * 1000;
	if (ac == 6)
		m->p.n_eats = ft_atolu(av[5]);
	return (1);
}

int	size_check(t_main *m)
{
	if (m->p.philo_nb >= INT_MAX)
		return (0);
	if (m->p.time_2die >= INT_MAX)
		return (0);
	if (m->p.time_2eat >= INT_MAX)
		return (0);
	if (m->p.time_2sleep >= INT_MAX)
		return (0);
	if (m->p.n_eats >= INT_MAX)
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
	if (!params_alloc(m, ac, av))
		return (0);
	if (!size_check(m))
	{
		ft_error(ERR_MAXINT);
		return (0);
	}
	gettimeofday(&m->t.start, NULL);
	return (1);
}
