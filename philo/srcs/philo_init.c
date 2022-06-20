/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/20 23:18:42 by seozcan          ###   ########.fr       */
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

int	size_check(t_main *m)
{
	if (m->philo_nb >= INT_MAX || m->philo_nb <= INT_MIN)
		return (0);
	if (m->time_2die >= INT_MAX)
		return (0);
	if (m->time_2eat >= INT_MAX)
		return (0);
	if (m->time_2sleep >= INT_MAX)
		return (0);
	if (m->n_eats >= INT_MAX || m->n_eats <= INT_MIN)
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
	m->philo_nb = ft_atoli(av[1]);
	if (m->philo_nb > MAX_THREADS)
		return (0);
	m->forks = m->philo_nb;
	m->time_2die = ft_atoli(av[2]);
	m->time_2eat = ft_atoli(av[3]);
	m->time_2sleep = ft_atoli(av[4]);
	if (ac == 6)
		m->n_eats = ft_atoli(av[5]);
	m->philosophers = malloc(sizeof(pthread_t) * m->philo_nb);
	if (!m->philosophers)
		return (0);	
	m->ret = malloc(sizeof(int) * m->philo_nb);
	if (!m->ret)
		return (0);
	if (!size_check(m))
	{
		ft_error(ERR_MAXINT);
		return (0);
	}
	return (1);
}
