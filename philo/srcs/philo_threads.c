/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/10 17:06:30 by seozcan          ###   ########.fr       */
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
	}
	return (1);
}

int	food_stock(t_main *m)
{
	if (read_data(&m->mt.satiated, &m->p[m->i].eat_counter) == m->n_eats)
		m->done_eating += 1;
	if (m->done_eating != m->philo_nb)
		return (1);
	return (0);
}

int	ecg(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		if (m->n_eats && !food_stock(m))
			break ;
		m->death_sentence = chrono(&m->mt.chrono, m->bigbang);
		if (m->death_sentence
			> read_udata(&m->mt.time[m->i], &m->p[m->i].expected_death))
		{
			write_data(&m->mt.reaper, &m->ghost, m->i + 1, 0);
			print_action(&m->p[m->i], DEAD);
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
