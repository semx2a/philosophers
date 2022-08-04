/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/04 19:53:23 by seozcan          ###   ########.fr       */
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
	return (1);
}

int	waiter(t_philos *p, int (*f)(pthread_mutex_t *), char *str)
{
	if (p->l_fork < p->r_fork)
	{
		if (!service(p, f, str, p->l_fork))
		{
			pthread_mutex_unlock(&p->m->mt.waiter[p->l_fork]);
			return (-1);
		}
		if (!service(p, f, str, p->r_fork))
			return (0);
	}
	else if (p->l_fork > p->r_fork)
	{
		if (!service(p, f, str, p->r_fork))
		{
			pthread_mutex_unlock(&p->m->mt.waiter[p->r_fork]);
			return (-1);
		}
		if (!service(p, f, str, p->l_fork))
			return (0);
	}
	else
	{
		service(p, f, str, p->l_fork);
		return (0);
	}
	return (1);
}
