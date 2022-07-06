/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/06 17:50:52 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_sleep(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.sleep);
	printf(SLEEPING, time_diff(&p->m->t), p->philo_id);
	usleep((p->m->t.time2_sleep));
	pthread_mutex_unlock(&p->m->mt.sleep);
}	

int	eat(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.fork_l);
	if (p->l_fork == 0 && p->r_fork == 0)
	{
		p->l_fork = 1;
		p->r_fork = 1;
		printf(FORK, time_diff(&p->m->t), p->philo_id);
		printf(EATING, time_diff(&p->m->t), p->philo_id);
		usleep((p->m->t.time2_eat));
		p->l_fork = 0;
		p->r_fork = 0;
	}
	else
	{
		pthread_mutex_unlock(&p->m->mt.fork_l);
		return (0);
	}
	pthread_mutex_unlock(&p->m->mt.fork_l);
	return (1);
}

void	think(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.think);
	printf(THINKING, time_diff(&p->m->t), p->philo_id);
	usleep(p->m->t.time2_sleep);
	pthread_mutex_unlock(&p->m->mt.think);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	if (eat(p) == 0)
		p_sleep(p);
	else
		think(p);
	return (NULL);
}
