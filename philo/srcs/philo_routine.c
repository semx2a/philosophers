/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/28 13:20:58 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_sleep(t_main *m)
{	
	pthread_mutex_lock(&m->mt.mutex);
	printf(SLEEPING, time_diff(&m->t), m->p.philo_id);
	usleep((m->t.time2_s));
	pthread_mutex_unlock(&m->mt.mutex);

}

int	eat(t_main *m)
{	
	pthread_mutex_lock(&m->mt.mutex);
	if (m->p.forks != 0)
	{
		m->p.forks -= 2;
		printf(FORK, time_diff(&m->t), m->p.philo_id);
		printf(EATING, time_diff(&m->t), m->p.philo_id);
		usleep((m->t.time2_e));
		m->p.forks += 2;
	}
	else
		return (0);
	pthread_mutex_unlock(&m->mt.mutex);
	return (1);
}

void	think(t_main *m)
{	
	pthread_mutex_lock(&m->mt.mutex);
	printf(THINKING, time_diff(&m->t), m->p.philo_id);
	pthread_mutex_unlock(&m->mt.mutex);
	usleep(m->t.time2_s);
}

void	*routine(void *p_data)
{
	t_main		*m;
	int			ret;

	m = (t_main *)p_data;
	pthread_mutex_lock(&m->mt.mutex);
	m->p.philo_id++;
	pthread_mutex_unlock(&m->mt.mutex);
	ret = eat(m);
	if (ret == 0)
		think(m);
	else
		p_sleep(m);
	return (NULL);
}
