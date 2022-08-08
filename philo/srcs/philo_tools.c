/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/08 17:58:37 by seozcan          ###   ########.fr       */
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

unsigned int	chrono(struct timeval bigbang)
{
	struct timeval	crt_time;

	gettimeofday(&crt_time, NULL);
	return ((unsigned)(((crt_time.tv_sec * 1000) + (crt_time.tv_usec / 1000))
		- ((bigbang.tv_sec * 1000) + (bigbang.tv_usec / 1000))));
}

int	print_action(t_philos *p, char *str)
{	
	if (ghost_buster(p))
		return (0);
	pthread_mutex_lock(&p->m->mt.display);
	printf(str, p->timestamp, p->philo_id);
	pthread_mutex_unlock(&p->m->mt.display);
	return (1);
}
