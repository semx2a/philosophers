/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/26 17:49:41 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philos *p)
{
	if (ghost_buster(p, 0))
		return (0);
	if (p->food_limit == 1 && p->eat_counter >= p->n_eats)
	{
		pthread_mutex_lock(&p->m->mt.satiated);
		p->m->done_eating += 1;
		if (p->m->done_eating >= p->m->philo_nb)
		{
			pthread_mutex_unlock(&p->m->mt.satiated);
			return (0);
		}
		pthread_mutex_unlock(&p->m->mt.satiated);
	}
	return (1);
}

int	p_sleep(t_philos *p)
{	
	if (ghost_buster(p, 0))
		return (0);
	print_action(SLEEPING, p, 1);
	usleep((useconds_t)(p->time2_sleep));
	return (1);
}

int	think(t_philos *p)
{
	if (ghost_buster(p, 0))
		return (0);
	if (p->philo_id % 1 == 0)
		usleep(p->time2_sleep / 2 + 1);
	print_action(THINKING, p, 1);
	return (1);
}

int	eat(t_philos *p)
{
	if (ghost_buster(p, 0))
		return (0);
	if (p->m->philo_nb == 1)
		return (0);
	pthread_mutex_lock(&p->m->mt.waiter[p->l_fork]);
	pthread_mutex_lock(&p->m->mt.waiter[p->r_fork]);
	if (!print_action(FORK, p, 2) || !print_action(EATING, p, 1))
	{	
		pthread_mutex_unlock(&p->m->mt.waiter[p->l_fork]);
		pthread_mutex_unlock(&p->m->mt.waiter[p->r_fork]);
		return (0);
	}
	p->time2_die += chrono(&p->m->t);
	if (p->food_limit == 1)
		p->eat_counter++;
	usleep((useconds_t)(p->time2_eat));
	pthread_mutex_unlock(&p->m->mt.waiter[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.waiter[p->r_fork]);
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	while (!read_data(p->m->mt.display, &p->m->start))
		usleep(50);
	while (1)
	{
		if (!eat(p))
			break ;
		if (!is_full(p))
			return (NULL);
		if (!p_sleep(p))
			break ;
		if (!think(p))
			break ;
	}
	return (NULL);
}
