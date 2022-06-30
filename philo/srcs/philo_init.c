/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:07 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/30 17:18:54 by seozcan          ###   ########.fr       */
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
	if (m->p.philo_nb > MAX_THREADS || m->p.philo_nb >= INT_MAX)
		return (0);
	m->t.time2_die = (useconds_t)ft_atolu(av[2]) * 1000;
	m->t.time2_eat = (useconds_t)ft_atolu(av[3]) * 1000;
	m->t.time2_sleep = (useconds_t)ft_atolu(av[4]) * 1000;
	if (ac == 6)
		m->p.n_eats = ft_atolu(av[5]);
	if (m->p.n_eats >= INT_MAX)
		return (0);
	m->p.philosophers = (pthread_t *)xmalloc(sizeof(pthread_t) * m->p.philo_nb);
	m->err = (int *)xmalloc(sizeof(int) * m->p.philo_nb);
	if (m->p.philo_nb != 1 && m->p.philo_nb % 1 == 0)
		m->p.forks = m->p.philo_nb - 1;
	else
		m->p.forks = m->p.philo_nb;
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
	{
		ft_error(ERR_ALLOC);
		return (0);
	}
	gettimeofday(&m->t.start, NULL);
	return (1);
}
