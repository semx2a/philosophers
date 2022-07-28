/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/28 18:58:15 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philos *p)
{	
	p->eat_counter++;
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
	if (!print_action(SLEEPING, p, 1))
		return (0);
	usleep((useconds_t)(p->time2_sleep));
	return (1);
}

int	think(t_philos *p)
{
	if (!print_action(THINKING, p, 1))
		return (0);
	return (1);
}

int	eat(t_philos *p)
{
	if (p->m->philo_nb == 1)
		return (0);
	waiter(p, &pthread_mutex_lock);
	if (!print_action(FORK, p, 2) || !print_action(EATING, p, 1))
	{
		waiter(p, &pthread_mutex_unlock);
		return (0);
	}
	p->time2_die += chrono(&p->m->t);
	usleep((useconds_t)(p->time2_eat));
	waiter(p, &pthread_mutex_unlock);
	if (p->food_limit == 1 && !is_full(p))
		return (0);
	if (!p_sleep(p))
		return (0);
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	while (!read_data(&p->m->mt.display, &p->m->start))
		usleep(200);
	p->time2_die += chrono(&p->m->t);
	if (p->philo_id % 2 == 0)
		usleep(p->time2_eat / 2);
	while (1)
	{
		if (!eat(p))
			break ;
		if (!think(p))
			break ;
	}
	return (NULL);
}
