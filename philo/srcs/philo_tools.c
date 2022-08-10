/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/10 14:46:42 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned int	chrono(pthread_mutex_t *m, struct timeval bigbang)
{
	unsigned int	ret;
	struct timeval	crt_time;

	pthread_mutex_lock(m);
	gettimeofday(&crt_time, NULL);
	ret = ((unsigned)(((crt_time.tv_sec * 1000) + (crt_time.tv_usec / 1000))
				- ((bigbang.tv_sec * 1000) + (bigbang.tv_usec / 1000))));
	pthread_mutex_unlock(m);
	return (ret);
}

int	print_action(t_philos *p, char *str)
{	
	p->timestamp = chrono(&p->m->mt.chrono, p->m->bigbang);
	if (!read_data(&p->m->mt.reaper, &p->m->ghost))
	{
		pthread_mutex_lock(&p->m->mt.display);
		printf(str, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.display);
		return (1);
	}
	return (0);
}
