/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:30:33 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/11 16:33:33 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philosophers_init(t_main *m)
{
	unsigned int	i;

	i = 0;
	while (i < m->philo_nb)
	{
		m->p[i].philo_id = i + 1;
		m->err[i] = pthread_create(&m->philosophers[i], NULL,
				&routine, &m->p[i]);
		if (m->err[i] != 0)
		{
			ft_error(ERR_THREAD);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philosophers_detach(t_main *m)
{
	unsigned int	i;

	i = 0;
	while (i < m->philo_nb)
	{
		if (pthread_detach(m->philosophers[i]))
			return (0);
		i++;
	}
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
