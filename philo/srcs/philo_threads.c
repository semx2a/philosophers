/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/09 23:05:18 by seozcan          ###   ########.fr       */
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

int	ecg(t_main *m)
{
	while (1)
	{
		m->i = 0;
		while (m->ghost == 0 && m->i < m->philo_nb)
		{
			m->death_sentence = chrono(m->bigbang);
			if (m->death_sentence
				> read_udata(&m->mt.time[m->i], &m->p[m->i].expected_death))
			{
				write_data(&m->mt.reaper, &m->ghost, 1, 0);
				pthread_mutex_lock(&m->mt.display);
				printf(DEAD, m->death_sentence, m->p[m->i].philo_id);
				pthread_mutex_unlock(&m->mt.display);
				return (1);
			}
			m->i++;
			usleep(200);
		}
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
