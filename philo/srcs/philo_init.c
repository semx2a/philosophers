/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/13 21:20:56 by seozcan          ###   ########.fr       */
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
			if (av[m->i][m->j] == '+' || av[m->i][m->j] == '-')
				m->j++;
			if (!ft_isdigit(av[m->i][m->j]))
				return (0);
			m->j++;
		}
		m->i++;
	}
	return (1);
}

int	size_check(t_main *m)
{
	if (m->philo_nb >= INT_MAX || m->philo_nb <= INT_MIN)
		return (0);
	if (m->time_2die >= INT_MAX || m->time_2die <= INT_MIN)
		return (0);
	if (m->time_2eat >= INT_MAX || m->time_2eat <= INT_MIN)
		return (0);
	if (m->time_2sleep >= INT_MAX || m->time_2sleep <= INT_MIN)
		return (0);
	if (m->u_eats >= INT_MAX || m->u_eats <= INT_MIN)
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
	m->philo_nb = ft_atoli(av[1]);
	m->time_2die = ft_atoli(av[2]);
	m->time_2eat = ft_atoli(av[3]);
	m->time_2sleep = ft_atoli(av[4]);
	if (ac == 6)
		m->u_eats = ft_atoli(av[5]);
	if (!size_check(m))
	{
		ft_error(ERR_MAXINT);
		return (0);
	}
	return (1);
}
