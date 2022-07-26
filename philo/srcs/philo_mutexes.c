/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/26 17:47:00 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	read_data(pthread_mutex_t mu, void *data)
{
	int	ret;

	pthread_mutex_lock(&mu);
	ret = *((int *)data);
	pthread_mutex_unlock(&mu);
	return (ret);
}

void	write_data(pthread_mutex_t mu, void *data, int value)
{
	if (data)
	{	
		pthread_mutex_lock(&mu);
		*((int *)data) = value;
		pthread_mutex_unlock(&mu);
		printf("start\n");
	}
}
