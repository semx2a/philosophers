/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2024/02/05 22:35:57 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_init(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{		
		m->bigbang[m->i] = chrono();
		m->p[m->i].birth = m->bigbang[m->i];
		m->expected_death[m->i] = (chrono() - m->bigbang[m->i])
			+ m->p[m->i].time2_die;
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
			> read_udata(&m->mt.time, &m->expected_death[m->i]))
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
