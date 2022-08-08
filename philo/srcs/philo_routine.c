/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/08 17:48:27 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philos *p)
{	
	p->eat_counter++;
	if (p->eat_counter == p->n_eats)
		write_data(&p->m->mt.satiated, &p->m->done_eating, 1, '+');
	if (read_data(&p->m->mt.satiated, &p->m->done_eating)
		== read_data(&p->m->mt.satiated, &p->m->philo_nb))
		return (0);
	return (1);
}

int	p_sleep(t_philos *p)
{	
	if (!print_action(p, SLEEPING))
		return (0);
	mr_sandman(p, p->time2_sleep);
	return (1);
}

int	think(t_philos *p)
{
	if (!print_action(p, THINKING))
		return (0);
	return (1);
}

int	eat(t_philos *p)
{
	p->err = waiter(p, &pthread_mutex_lock, FORK);
	if (p->err == -2 || p->err == -1 || p->err == 0)
	{
		if (p->err == -1 || p->err == -2)
			waiter(p, &pthread_mutex_unlock, NULL);
		return (0);
	}
	if (!print_action(p, EATING))
	{
		waiter(p, &pthread_mutex_unlock, NULL);
		return (0);
	}
	p->expected_death = p->timestamp + p->time2_die;
	mr_sandman(p, p->time2_eat);
	waiter(p, &pthread_mutex_unlock, NULL);
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
	p->expected_death = chrono(p->m->bigbang) + p->time2_die;
	if (p->philo_id % 2 == 0)
		mr_sandman(p, p->offset);
	while (!ghost_buster(p))
	{
		if (!eat(p))
			break ;
		if (!think(p))
			break ;
	}
	return (NULL);
}
