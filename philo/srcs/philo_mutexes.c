/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/05 16:50:50 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	read_data(pthread_mutex_t *mu, int *data)
{
	int	ret;

	pthread_mutex_lock(mu);
	ret = *data;
	pthread_mutex_unlock(mu);
	return (ret);
}

void	write_data(pthread_mutex_t *mu, int *data, int value, char instruction)
{
	pthread_mutex_lock(mu);
	if (instruction == '+')
		*(data) += value;
	else
		*(data) = value;
	pthread_mutex_unlock(mu);
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
		return (-1);
	}
	if (!service(p, f, str, f2))
		return (0);
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
