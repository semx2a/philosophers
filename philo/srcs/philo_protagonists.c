/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_protagonists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/16 17:39:19 by seozcan          ###   ########.fr       */
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

int	inspect_platter(t_philos *p, int action, int f1, int f2)
{
	if (!service(p, f1, action))
		return (0);
	if (!service(p, f2, action))
		return (0);
	return (1);
}

int	platter(t_philos *p, int action)
{
	if (p->l_fork < p->r_fork)
	{
		if (!inspect_platter(p, action, p->l_fork, p->r_fork))
			return (0);
	}
	else if (p->l_fork > p->r_fork)
	{
		if (!inspect_platter(p, action, p->r_fork, p->l_fork))
			return (0);
	}
	else
	{
		service(p, p->l_fork, action);
		mr_sandman(p, p->birth + p->time2_die);
		return (0);
	}
	return (1);
}
