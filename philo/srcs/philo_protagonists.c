/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_protagonists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/08 17:59:42 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	mr_sandman(t_philos *p, unsigned int time)
{
	unsigned int	countdown;

	countdown = chrono(p->m->bigbang) + time;
	while (chrono(p->m->bigbang) < countdown && !ghost_buster(p))
		usleep(1);
}

int	ghost_buster(t_philos *p)
{	
	p->timestamp = chrono(p->m->bigbang);
	if (read_data(&p->m->mt.reaper, &p->m->ghost) != 0)
		return (1);
	else if (!read_data(&p->m->mt.reaper, &p->m->ghost)
		&& p->timestamp > p->expected_death)
	{
		write_data(&p->m->mt.reaper, &p->m->ghost, (int)p->philo_id, 0);
		pthread_mutex_lock(&p->m->mt.display);
		printf(DEAD, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.display);
		return (1);
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

int	waiter(t_philos *p, int (*f)(pthread_mutex_t *), char *str)
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
		while (!ghost_buster(p))
			usleep(1);
	}
	return (ret);
}
