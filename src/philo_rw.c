/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:54:46 by seozcan           #+#    #+#             */
/*   Updated: 2024/02/05 22:35:57 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (instruction == '-')
		*(data) -= value;
	else
		*(data) = value;
	pthread_mutex_unlock(mu);
}

unsigned int	read_udata(pthread_mutex_t *mu, unsigned int *data)
{
	unsigned int	ret;

	pthread_mutex_lock(mu);
	ret = *data;
	pthread_mutex_unlock(mu);
	return (ret);
}

void	write_udata(pthread_mutex_t *mu, unsigned int *data, unsigned int value)
{
	pthread_mutex_lock(mu);
	*(data) = value;
	pthread_mutex_unlock(mu);
}
