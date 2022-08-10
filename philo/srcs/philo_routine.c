/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/10 19:03:36 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	write_data(&p->m->mt.satiated, &p->eat_counter, 1, '-');
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	if (p->philo_id % 2 == 0)
		usleep(10000);
	p->timestamp = chrono(&p->m->mt.chrono, p->m->bigbang);
	write_udata(&p->m->mt.time[p->philo_id - 1], &p->expected_death,
		p->timestamp + p->time2_die, 0);
	while (!(read_data(&p->m->mt.satiated, &p->m->end_of_service)))
	{
		if (!eat(p))
			break ;
		else
			if (!p_sleep(p))
				return (NULL);
		if (!print_action(p, THINKING))
			break ;
	}
	return (NULL);
}
