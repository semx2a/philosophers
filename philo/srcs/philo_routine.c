/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/09 23:09:21 by seozcan          ###   ########.fr       */
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
	if (!mr_sandman(p, p->time2_sleep))
		return (0);
	return (1);
}

int	eat(t_philos *p)
{
	if (!waiter(p, 1))
		return (0);
	if (!print_action(p, EATING))
	{	
		waiter(p, 0);
		return (0);
	}
	write_udata(&p->m->mt.time[p->philo_id - 1], &p->expected_death,
		p->timestamp + p->time2_die, 0);
	if (!mr_sandman(p, p->time2_eat))
	{	
		waiter(p, 0);
		return (0);
	}
	waiter(p, 0);
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	p->timestamp = chrono(p->m->bigbang);
	write_udata(&p->m->mt.time[p->philo_id - 1], &p->expected_death,
		p->timestamp + p->time2_die, 0);
	while (1)
	{
		if (!eat(p))
			break ;
		else
		{
			if (p->food_limit == 1 && !is_full(p))
				return (NULL);
			if (!p_sleep(p))
				return (NULL);
		}
		if (!print_action(p, THINKING))
			break ;
		usleep(10);
	}
	return (NULL);
}
