/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/15 23:57:22 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	eat(t_philos *p)
{
	if (platter(p, 1))
	{
		if (!print_action(p, EATING))
			return (0);
		write_udata(&p->m->mt.time, &p->m->expected_death[p->philo_id - 1],
			p->timestamp + p->time2_die);
		mr_sandman(p, p->time2_eat);
		platter(p, 0);
		if (p->eat_counter)
			p->eat_counter -= 1;
		else
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
		{
			print_action(p, SLEEPING);
			mr_sandman(p, p->time2_sleep);
		}
		print_action(p, THINKING);
	}
	return (NULL);
}
