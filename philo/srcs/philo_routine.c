/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/12 22:55:34 by seozcan          ###   ########.fr       */
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

int	is_full(t_philos *p)
{
	if (p->m->food_limit == 1 && p->eat_counter == p->n_eats)
	{
		pthread_mutex_lock(&p->m->mt.satiated);
		p->m->done_eating += 1;
		if (p->m->done_eating == p->m->philo_nb)
		{	
			pthread_mutex_unlock(&p->m->mt.satiated);
			return (0);
		}
		pthread_mutex_unlock(&p->m->mt.satiated);
	}
	return (1);
}

int	eat(t_philos *p)
{
	if (p->m->philo_nb == 1)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->l_fork]) != 0)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->r_fork]) != 0)
		return (0);
	print_action(2, p);
	print_action(3, p);
	if (p->m->food_limit == 1)
		p->eat_counter++;
	usleep((useconds_t)(p->m->t.time2_eat));
	pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.forks[p->r_fork]);
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
	while (chrono(&p->m->t) < p->red_tape)
	{
		pthread_mutex_lock(&p->m->mt.reaper);
		if (p->m->ghost == 0)
		{
			pthread_mutex_unlock(&p->m->mt.reaper);
			if (eat(p) == 1)
				p_sleep(p);
			if (!is_full(p))
				return (NULL);
			think(p);
		}
		else
			break ;
	}
	p->m->ghost = 1;
	print_action(0, p);
//	philosophers_detach(p->m);
	return (NULL);
}
