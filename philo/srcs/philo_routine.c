/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/06 20:56:37 by seozcan          ###   ########.fr       */
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

void	eat(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_lock(&p->m->mt.forks[p->r_fork]);
	printf(FORK, time_diff(&p->m->t), p->philo_id);
	printf(EATING, time_diff(&p->m->t), p->philo_id);
	usleep((p->m->t.time2_eat));
	pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.forks[p->r_fork]);
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
	while (1)
	{	
		eat(p);
		p_sleep(p);
		think(p);
	}
	return (NULL);
}
