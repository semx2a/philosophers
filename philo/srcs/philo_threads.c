/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/11 18:14:06 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philosophers_init(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{		
		m->bigbang[m->i] = chrono();
		m->p[m->i].birth = m->bigbang[m->i];
		m->err[m->i] = pthread_create(&m->philosophers[m->i], NULL,
				&routine, &m->p[m->i]);
		if (m->err[m->i] != 0)
		{
			ft_error(ERR_THREAD);
			return (0);
		}
		m->i++;
	}
	return (1);
}

int	ecg(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (m->stock_limit && !read_data(&m->mt.display, &m->done_eating))
		{
			write_data(&m->mt.display, &m->stop, 1, 0);
			break ;
		}
		if ((chrono() - m->bigbang[m->i])
			> read_udata(&m->mt.time[m->i], &m->p[m->i].expected_death))
		{
			write_data(&m->mt.display, &m->stop, 1, 0);
			pthread_mutex_lock(&m->mt.display);
			printf(DEAD, chrono() - m->bigbang[m->i], m->i + 1);
			pthread_mutex_unlock(&m->mt.display);
			break ;
		}
		m->i++;
		if (m->i == m->philo_nb)
			m->i = 0;
	}
	return (1);
}

int	philosophers_join(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (pthread_join(m->philosophers[m->i],
				(void *)(intptr_t)m->err[m->i]) != 0)
			return (0);
		m->i++;
	}
	return (1);
}
