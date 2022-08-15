/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_protagonists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/15 23:59:58 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	mr_sandman(t_philos *p, unsigned int time)
{
	unsigned int	countdown;

	countdown = chrono();
	while (!read_data(&p->m->mt.display, &p->m->stop))
	{
		if (chrono() - countdown >= time)
			return (1);
		usleep(50);
	}
	return (0);
}

int	service(t_philos *p, int fork, int action)
{
	if (action == 1 && !read_data(&p->m->mt.waiter[fork], &p->m->platter[fork]))
	{
		write_data(&p->m->mt.waiter[fork], &p->m->platter[fork], action, 0);
		if (!print_action(p, FORK))
			return (0);
		return (1);
	}
	else if (action == 0
		&& read_data(&p->m->mt.waiter[fork], &p->m->platter[fork]))
	{
		write_data(&p->m->mt.waiter[fork], &p->m->platter[fork], action, 0);
		return (1);
	}
	return (0);
}

int	platter(t_philos *p, int action)
{
	if (p->l_fork < p->r_fork)
	{
		if (!service(p, p->l_fork, action))
		{
			service(p, p->l_fork, 0);
			return (0);
		}
		service(p, p->r_fork, action);
	}
	else if (p->l_fork > p->r_fork)
	{
		if (!service(p, p->r_fork, action))
		{
			service(p, p->r_fork, 0);
			return (0);
		}
		service(p, p->l_fork, action);
	}
	else
	{
		service(p, p->l_fork, action);
		mr_sandman(p, p->time2_die);
		return (0);
	}
	return (1);
}
