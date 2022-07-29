/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/29 16:57:48 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ghost_buster(t_philos *p)
{
	if (!read_data(&p->m->mt.reaper, &p->m->ghost)
		&& p->timestamp > p->time2_die)
	{
		write_data(&p->m->mt.reaper, &p->m->ghost, (int)p->philo_id, 0);
		pthread_mutex_lock(&p->m->mt.display);
		printf(DEAD, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.display);
		return (1);
	}
	else if (read_data(&p->m->mt.reaper, &p->m->ghost) != 0)
		return (1);
	return (0);
}

int	print_action(t_philos *p, char *str)
{
	p->timestamp = chrono(&p->m->t);
	if (ghost_buster(p))
		return (0);
	pthread_mutex_lock(&p->m->mt.display);
	printf(str, p->timestamp, p->philo_id);
	pthread_mutex_unlock(&p->m->mt.display);
	return (1);
}

int	service(t_philos *p, int (*f)(pthread_mutex_t *), char *str, int fork)
{
	f(&p->m->mt.waiter[fork]);
	if (str != NULL)
		if (!print_action(p, str))
			return (0);
	return (1);
}

int	waiter(t_philos *p, int (*f)(pthread_mutex_t *), char *str)
{
	if (p->l_fork < p->r_fork)
	{
		if (!service(p, f, str, p->l_fork))
			return (0);
		if (!service(p, f, str, p->r_fork))
			return (0);
	}
	else
	{
		if (!service(p, f, str, p->r_fork))
			return (0);
		if (!service(p, f, str, p->l_fork))
			return (0);
	}
	return (1);
}

void	ft_flush(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		pthread_mutex_destroy(&m->mt.waiter[m->i]);
		m->i++;
	}
	pthread_mutex_destroy(&m->mt.satiated);
	pthread_mutex_destroy(&m->mt.display);
	pthread_mutex_destroy(&m->mt.reaper);
	free(m->mt.waiter);
	free(m->p);
	free(m->philosophers);
	free(m->err);
}
