/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/19 22:28:54 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned long	chrono(t_time *t)
{
	long	current;
	long	begin;

	gettimeofday(&t->step, NULL);
	current = (t->step.tv_sec * 1000) + (t->step.tv_usec / 1000);
	begin = (t->start.tv_sec * 1000) + (t->start.tv_usec / 1000);
	return ((unsigned long)(current - begin));
}

int	ghost_buster(t_philos *p, int radar)
{
	pthread_mutex_lock(&p->m->mt.reaper);
	if (p->m->ghost != 0)
	{
		pthread_mutex_unlock(&p->m->mt.reaper);
		return (1);
	}
	else if (!p->m->ghost && radar == 1)
	{
		p->m->ghost = (int)p->philo_id;
		p->timestamp = chrono(&p->m->t);
		printf(DEAD, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.reaper);
		return (1);
	}
	pthread_mutex_unlock(&p->m->mt.reaper);
	return (0);
}

int	print_action(char *s, t_philos *p, pthread_mutex_t *m1, pthread_mutex_t *m2)
{
	if (ghost_buster(p, 0))
	{
		pthread_mutex_unlock(m1);
		if (m2 != NULL)
			pthread_mutex_unlock(m2);
		return (0);
	}
	pthread_mutex_lock(&p->m->mt.display);
	p->timestamp = chrono(&p->m->t);
	printf(s, p->timestamp, p->philo_id);
	if (m2 != NULL)
		printf(s, p->timestamp, p->philo_id);
	pthread_mutex_unlock(&p->m->mt.display);
	return (1);
}

void	ft_flush(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		pthread_mutex_destroy(&m->mt.forks[m->i]);
		m->i++;
	}
	pthread_mutex_destroy(&m->mt.sleep);
	pthread_mutex_destroy(&m->mt.think);
	pthread_mutex_destroy(&m->mt.satiated);
	pthread_mutex_destroy(&m->mt.display);
	pthread_mutex_destroy(&m->mt.reaper);
	free(m->mt.forks);
	free(m->p);
	free(m->philosophers);
	free(m->err);
}
