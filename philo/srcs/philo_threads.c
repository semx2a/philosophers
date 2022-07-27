/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/27 20:17:32 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philosophers_init(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{	
		m->p[m->i].philo_id = (int)m->i + 1;
		m->err[m->i] = pthread_create(&m->philosophers[m->i], NULL,
				&routine, &m->p[m->i]);
		if (m->err[m->i] != 0)
		{
			ft_error(ERR_THREAD);
			return (0);
		}
		m->i++;
	}
//	write_data(m->mt.display, &m->start, 1);
	return (1);
}

int	philosophers_join(t_main *m)
{
	unsigned int	i;

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
