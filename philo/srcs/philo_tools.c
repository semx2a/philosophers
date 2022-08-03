/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/03 17:49:46 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ghost_buster(t_philos *p)
{
	if (!read_data(&p->m->mt.reaper, &p->m->ghost)
		&& chrono(p->m->bigbang) > p->expected_death)
	{
		write_data(&p->m->mt.reaper, &p->m->ghost, (int)p->philo_id, 0);
		pthread_mutex_lock(&p->m->mt.display);
		printf(DEAD, p->timestamp, p->philo_id);
		pthread_mutex_unlock(&p->m->mt.display);
		return (1);
	}
	else if (read_data(&p->m->mt.reaper, &p->m->ghost) != 0)
		return (1);
	return (0);
}

int	print_action(t_philos *p, char *str)
{
	(void)str;
	if (ghost_buster(p))
		return (0);
	pthread_mutex_lock(&p->m->mt.display);
	p->timestamp = chrono(p->m->bigbang);
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
