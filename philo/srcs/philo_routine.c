/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/19 22:28:49 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philos *p)
{
	if (pthread_mutex_lock(&p->m->mt.satiated) != 0)
		return (0);
	if (p->m->food_limit == 1 && p->eat_counter == p->n_eats)
	{
		p->m->done_eating += 1;
		if (p->m->done_eating == p->m->philo_nb)
		{	
			pthread_mutex_unlock(&p->m->mt.satiated);
			return (0);
		}
	}
	pthread_mutex_unlock(&p->m->mt.satiated);
	return (1);
}

int	p_sleep(t_philos *p)
{
	if (pthread_mutex_lock(&p->m->mt.sleep) != 0)
		return (0);
	if (!print_action(SLEEPING, p, &p->m->mt.sleep, NULL))
		return (0);
	usleep((useconds_t)(p->m->t.time2_sleep));
	pthread_mutex_unlock(&p->m->mt.sleep);
	return (1);
}	

int	eat(t_philos *p)
{	
	if (p->m->philo_nb == 1)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->l_fork]) != 0)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->r_fork]) != 0)
	{
		pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
		return (0);
	}
	if (!print_action(FORK, p, &p->m->mt.forks[p->l_fork],
			&p->m->mt.forks[p->r_fork]))
		return (0);
	if (!print_action(EATING, p, &p->m->mt.forks[p->l_fork], NULL))
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
	if (pthread_mutex_lock(&p->m->mt.think) != 0)
		return (0);
	if (!print_action(THINKING, p, &p->m->mt.think, NULL))
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
		if (eat(p))
		{
			if (!p_sleep(p))
				break ;
			if (!is_full(p))
				return (NULL);
		}
		else
			if (!think(p))
				break ;
	}
	ghost_buster(p, 1);
	return (NULL);
}
