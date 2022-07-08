/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/08 21:53:38 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned long	time_diff(t_time *t)
{
	long	current;
	long	begin;

	gettimeofday(&t->step, NULL);
	current = (t->step.tv_sec * 1000) + (t->step.tv_usec / 1000);
	begin = (t->start.tv_sec * 1000) + (t->start.tv_usec / 1000);
	return ((unsigned long)(current - begin));
}

void	lock_action(t_philos *p, char *str, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	printf(str, time_diff(&p->m->t), p->philo_id);
	pthread_mutex_unlock(m);
}

void	print_action(int i, t_philos *p)
{
	if (i == 0)
		lock_action(p, DEAD, &p->m->mt.print_dead);
	else if (i == 1)
		lock_action(p, SLEEPING, &p->m->mt.print_sleep);
	else if (i == 2)
	{
		lock_action(p, FORK, &p->m->mt.print_fork);
		lock_action(p, FORK, &p->m->mt.print_fork);
	}
	else if (i == 3)
	{
		p->red_tape = time_diff(&p->m->t) + p->m->t.time2_die;
		lock_action(p, EATING, &p->m->mt.print_eat);
	}
	else if (i == 4)
		lock_action(p, THINKING, &p->m->mt.print_think);
}
