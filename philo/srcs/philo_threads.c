/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/09 18:32:48 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philosophers_init(t_main *m)
{
	m->i = 0;
	gettimeofday(&m->bigbang, NULL);
	while (m->i < m->philo_nb)
	{	
		m->err[m->i] = pthread_create(&m->philosophers[m->i], NULL,
				&routine, &m->p[m->i]);
		if (m->err[m->i] != 0)
		{
			ft_error(ERR_THREAD);
			return (0);
		}
		usleep(10);
		m->i++;
	}
	return (1);
}

int	philosophers_join(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_nb)
	{
		if (pthread_join(m->philosophers[i],
				(void *)(intptr_t)m->err[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
