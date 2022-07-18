/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/18 19:13:22 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	p_sleep(t_philos *p)
{
	pthread_mutex_lock(&p->m->mt.sleep);
	if (print_action(SLEEPING, p) == 0)
		return (0);
	usleep((useconds_t)(p->m->t.time2_sleep));
	pthread_mutex_unlock(&p->m->mt.sleep);
	return (1);
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
//	printf("philo == %lu : l_fork == %lu | r_fork == %lu\n", p->philo_id, p->l_fork, p->r_fork);
	if (p->m->philo_nb == 1)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->l_fork]) != 0)
		return (0);
	if (print_action(FORK, p) == 0)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->r_fork]) != 0)
	{
		pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
		return (0);
	}
	if (print_action(FORK, p) == 0)
		return (0);
	if (print_action(EATING, p) == 0)
		return (0);
	if (p->m->food_limit == 1)
		p->eat_counter++;
	usleep((useconds_t)(p->m->t.time2_eat));
	pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.forks[p->r_fork]);
	return (1);
}

int	think(t_philos *p)
{	
	pthread_mutex_lock(&p->m->mt.think);
	if (print_action(THINKING, p) == 0)
		return (0);
	usleep((useconds_t)p->m->t.time2_sleep);
	pthread_mutex_unlock(&p->m->mt.think);
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	while (chrono(&p->m->t) < p->red_tape)
	{		
		if (eat(p) == 1)
		{
			if (p_sleep(p) == 0)
				break ;
			if (!is_full(p))
				return (NULL);
		}
		else
			if (think(p) == 0)
				break ;
	}
	pthread_mutex_lock(&p->m->mt.reaper);
	if (p->m->ghost == 0)
	{
		p->m->ghost = (int)p->philo_id;
		p->timestamp = chrono(&p->m->t);
		printf(DEAD, p->timestamp, p->philo_id);
	}
	pthread_mutex_unlock(&p->m->mt.reaper);
	return (NULL);
}
