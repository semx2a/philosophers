/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/10 18:32:35 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_params(t_main *m, int ac, char **av)
{
	m->i = 1;
	while (m->i <= ac)
	{
		while (av[m->i][m->j])
		{
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
	if (m->time_2die >= INT_MAX || m->philo_nb <= INT_MIN)
		return (0);
	if (m->time_2eat >= INT_MAX || m->philo_nb <= INT_MIN)
		return (0);
	if (m->time_2sleep >= INT_MAX || m->philo_nb <= INT_MIN)
		return (0);
	if (m->u_eats >= INT_MAX || m->philo_nb <= INT_MIN)
		return (0);
	return (1);
}

int	init_params(t_main *m, int ac, char **av)
{	
	if (!check_params(m, ac, av))
		return (0);
	m->philo_nb = ft_atoli(av[1]);
	m->time_2die = ft_atoli(av[2]);
	m->time_2eat = ft_atoli(av[3]);
	m->time_2sleep = ft_atoli(av[4]);
	if (ac == 5)
		m->u_eats = ft_atoli(av[5]);
	if (!size_check(m))
		return (0);
	return (1);
}
