/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/07 19:35:31 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_action(int i, t_philos *p)
{
	pthread_mutex_lock(&p->m->mt.print);
	if (i == 0)
		printf(DEAD, time_diff(&p->m->t), p->philo_id);
	else if (i == 1)
		printf(SLEEPING, time_diff(&p->m->t), p->philo_id);
	else if (i == 2)
	{
		printf(FORK, time_diff(&p->m->t), p->philo_id);
		printf(FORK, time_diff(&p->m->t), p->philo_id);
	}
	else if (i == 3)
		printf(EATING, time_diff(&p->m->t), p->philo_id);
	else if (i == 4)
		printf(THINKING, time_diff(&p->m->t), p->philo_id);
	pthread_mutex_unlock(&p->m->mt.print);

}

void	p_sleep(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.sleep);
	print_action(1, p);
	usleep((p->m->t.time2_sleep));
	pthread_mutex_unlock(&p->m->mt.sleep);
}	

int	eat(t_philos *p)
{	
	if (pthread_mutex_lock(&p->m->mt.forks[p->l_fork]) != 0)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->r_fork]) != 0)
		return (0);
	print_action(2, p);
	print_action(3, p);
	usleep((p->m->t.time2_eat));
	pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.forks[p->r_fork]);
	return (1);
}

void	think(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.think);
	print_action(4, p);
	usleep(p->m->t.time2_sleep);
	pthread_mutex_unlock(&p->m->mt.think);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	while (1)
	{	
		if (eat(p))
			p_sleep(p);
		else
			think(p);
	}
	return (NULL);
}
