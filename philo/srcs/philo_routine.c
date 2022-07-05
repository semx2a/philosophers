/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/04 16:16:02 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_sleep(t_main *m)
{	
	pthread_mutex_lock(&m->mt.sleep);
	printf(SLEEPING, time_diff(&m->t), m->p.philo_id);
	usleep((m->t.time2_sleep));
	pthread_mutex_unlock(&m->mt.sleep);
}	

int	eat(t_main *m)
{	
	pthread_mutex_lock(&m->mt.fork_l);
	if (m->p.l_fork == 0)
	{
		m->p.l_fork = 1;
		printf(FORK, time_diff(&m->t), m->p.philo_id);
		printf(EATING, time_diff(&m->t), m->p.philo_id);
		usleep((m->t.time2_eat));
		m->p.l_fork = 0;
	}
	else
	{
		pthread_mutex_unlock(&m->mt.fork_l);
		return (0);
	}
	pthread_mutex_unlock(&m->mt.fork_l);
	return (1);
}

void	think(t_main *m)
{	
	pthread_mutex_lock(&m->mt.think);
	printf(THINKING, time_diff(&m->t), m->p.philo_id);
	usleep(m->t.time2_sleep);
	pthread_mutex_unlock(&m->mt.think);
}

void	*routine(void *p_data)
{
	t_main		*m;

	m = (t_main *)p_data;
	pthread_mutex_lock(&m->mt.mutex);
	m->p.philo_id++;
	pthread_mutex_unlock(&m->mt.mutex);
	if (eat(m) == 0)
		p_sleep(m);
	else
		think(m);
	return (NULL);
}
