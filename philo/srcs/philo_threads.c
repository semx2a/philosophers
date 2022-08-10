/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/10 19:08:17 by seozcan          ###   ########.fr       */
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
		m->i++;
		usleep(10);
	}
	return (1);
}

int	food_stock(t_main *m)
{
	int	ret;

	ret = 0;
	m->j = 0;
	if (read_data(&m->mt.satiated, &m->p[m->i].eat_counter) <= 0)
		m->done_eating[m->i] = 1;
	while (m->j < m->philo_nb)
	{
		ret += m->done_eating[m->j];
		if (ret == m->philo_nb)
			return (1);
		m->j++;
	}
	return (0);
}

int	ecg(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (m->stock_limit && food_stock(m))
		{
			write_data(&m->mt.satiated, &m->end_of_service, 1, 0);
			break ;
		}
		if (chrono(&m->mt.chrono, m->bigbang)
			> read_udata(&m->mt.time[m->i], &m->p[m->i].expected_death))
		{
			write_data(&m->mt.reaper, &m->ghost, m->i + 1, 0);
			pthread_mutex_lock(&m->mt.display);
			printf(DEAD, chrono(&m->mt.chrono, m->bigbang), m->i + 1);
			pthread_mutex_unlock(&m->mt.display);
			break ;
		}
		m->i++;
		if (m->i == m->philo_nb)
			m->i = 0;
		usleep(200);
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
