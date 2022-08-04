/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/04 19:36:16 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned int	chrono(struct timeval bigbang)
{
	struct timeval	crt_time;

	gettimeofday(&crt_time, NULL);
	return ((unsigned)(((crt_time.tv_sec * 1000) + (crt_time.tv_usec / 1000))
		- ((bigbang.tv_sec * 1000) + (bigbang.tv_usec / 1000))));
}

int	ghost_buster(t_philos *p)
{	
	p->timestamp = chrono(p->m->bigbang);
	if (read_data(&p->m->mt.reaper, &p->m->ghost) != 0)
		return (1);
	else if (!read_data(&p->m->mt.reaper, &p->m->ghost)
		&& p->timestamp > p->expected_death)
	{
		write_data(&p->m->mt.reaper, &p->m->ghost, (int)p->philo_id, 0);
		pthread_mutex_lock(&p->m->mt.display);
		printf(DEAD, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.display);
		return (1);
	}
	return (0);
}

int	print_action(t_philos *p, char *str)
{	
	if (ghost_buster(p))
		return (0);
	pthread_mutex_lock(&p->m->mt.display);
	printf(str, p->timestamp, p->philo_id);
	pthread_mutex_unlock(&p->m->mt.display);
	return (1);
}

void	ft_flush(t_main *m)
{
	m->i = 0;
	while (m->i < m->philo_nb)
	{
		pthread_mutex_destroy(&m->mt.waiter[m->i]);
		m->i++;
	}
	pthread_mutex_destroy(&m->mt.satiated);
	pthread_mutex_destroy(&m->mt.display);
	pthread_mutex_destroy(&m->mt.reaper);
	free(m->mt.waiter);
	free(m->p);
	free(m->philosophers);
	free(m->err);
}

void	mr_sandman(t_philos *p, unsigned int time)
{
	unsigned int	countdown;

	countdown = chrono(p->m->bigbang) + (time / 1000);
	while (chrono(p->m->bigbang) < countdown && !ghost_buster(p))
		usleep(1);
}
