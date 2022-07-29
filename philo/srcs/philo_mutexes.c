/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:49:13 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/29 16:32:25 by seozcan          ###   ########.fr       */
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
