/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_protagonists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2024/02/05 22:35:57 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	service(t_philos *p, int (*f)(pthread_mutex_t *), char *str, int fork)
{
	f(&p->m->mt.waiter[fork]);
	if (str != NULL)
		if (!print_action(p, str))
			return (0);
	if (p->l_fork == p->r_fork)
		return (-2);
	return (1);
}

int	inspect_platter(t_philos *p, int (*f)(pthread_mutex_t *), char *str, int f1,
			int f2)
{
	if (!service(p, f, str, f1))
	{
		pthread_mutex_unlock(&p->m->mt.waiter[f1]);
		return (0);
	}
	if (!service(p, f, str, f2))
		return (-1);
	return (1);
}

int	platter(t_philos *p, int (*f)(pthread_mutex_t *), char *str)
{
	int	ret;

	ret = 0;
	if (p->l_fork < p->r_fork)
		ret = inspect_platter(p, f, str, p->l_fork, p->r_fork);
	else if (p->l_fork > p->r_fork)
		ret = inspect_platter(p, f, str, p->r_fork, p->l_fork);
	else
	{
		ret = service(p, f, str, p->l_fork);
		mr_sandman(p, p->time2_die);
	}
	return (ret);
}

int	waiter(t_philos *p, int val)
{
	if (val == 1)
	{
		p->err = platter(p, &pthread_mutex_lock, FORK);
		if (p->err != 1)
		{
			if (p->err != 0)
				platter(p, &pthread_mutex_unlock, NULL);
			return (0);
		}
	}
	else if (!val)
		platter(p, &pthread_mutex_unlock, NULL);
	return (1);
}
