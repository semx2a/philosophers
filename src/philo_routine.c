/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2024/02/05 22:35:57 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	write_udata(&p->m->mt.time, &p->m->expected_death[p->philo_id - 1],
		p->timestamp + p->time2_die);
	if (!mr_sandman(p, p->time2_eat))
	{	
		waiter(p, 0);
		return (0);
	}
	waiter(p, 0);
	if (p->eat_counter)
	{
		p->eat_counter -= 1;
		if (!p->eat_counter)
			write_data(&p->m->mt.display, &p->m->done_eating, 1, '-');
	}
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	if (p->philo_id % 2 == 0)
		usleep(10000);
	while (!read_data(&p->m->mt.display, &p->m->stop))
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
