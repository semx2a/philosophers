/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/08 22:03:58 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	p_sleep(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.sleep);
	print_action(1, p);
	usleep((useconds_t)(p->m->t.time2_sleep));
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
	if (p->m->food_limit == 1)
		p->n_eats--;
	usleep((useconds_t)(p->m->t.time2_eat));
	pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.forks[p->r_fork]);
	p_sleep(p);
	return (1);
}

void	think(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.think);
	print_action(4, p);
	usleep((useconds_t)p->m->t.time2_sleep);
	pthread_mutex_unlock(&p->m->mt.think);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	while (p->red_tape <= time_diff(&p->m->t))
	{
		if (p->m->food_limit == 1)
		{
			eat(p);
			think(p);
			if (p->n_eats == 0)
				return (NULL);
		}
		else
		{
			eat(p);
			think(p);
		}
	}
	print_action(0, p);
	return (NULL);
}
