/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2024/02/05 22:35:57 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	chrono(void)
{
	struct timeval	crt_time;

	gettimeofday(&crt_time, NULL);
	return ((unsigned)((crt_time.tv_sec * 1000) + (crt_time.tv_usec / 1000)));
}

int	print_action(t_philos *p, char *str)
{	
	pthread_mutex_lock(&p->m->mt.display);
	if (!p->m->stop)
	{
		p->timestamp = chrono() - p->birth;
		printf(str, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.display);
		return (1);
	}
	pthread_mutex_unlock(&p->m->mt.display);
	return (0);
}
