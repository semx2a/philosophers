/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/21 19:01:15 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philos *p)
{
	if (p->food_limit == 1 && p->eat_counter == p->n_eats)
	{
		if (pthread_mutex_lock(&p->m->mt.satiated) != 0)
			return (0);
		p->m->done_eating += 1;
		if (p->m->done_eating >= p->m->philo_nb)
		{
			printf("ok\n");
			pthread_mutex_unlock(&p->m->mt.satiated);
			return (0);
		}
		pthread_mutex_unlock(&p->m->mt.satiated);
	}
	return (1);
}

int	p_sleep(t_philos *p)
{
	if (!print_action(SLEEPING, p, &p->m->mt.sleep, NULL))
		return (0);
	usleep((useconds_t)(p->time2_sleep));
	return (1);
}	

int	eat(t_philos *p)
{	
	if (p->m->philo_nb == 1)
		return (0);
	if (pthread_mutex_lock(&p->m->mt.forks[p->l_fork]) != 0
		|| pthread_mutex_lock(&p->m->mt.forks[p->r_fork]) != 0)
		return (0);
	if (!print_action(FORK, p, &p->m->mt.forks[p->l_fork],
			&p->m->mt.forks[p->r_fork]))
		return (0);
	if (!print_action(EATING, p, &p->m->mt.forks[p->l_fork], NULL))
		return (0);
	p->time2_die += chrono(&p->m->t);
	if (p->food_limit == 1)
		p->eat_counter++;
	usleep((useconds_t)(p->time2_eat));
	pthread_mutex_unlock(&p->m->mt.forks[p->l_fork]);
	pthread_mutex_unlock(&p->m->mt.forks[p->r_fork]);
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	while (!ghost_buster(p, 0) && chrono(&p->m->t) < p->time2_die)
	{	
		if (!eat(p))
			break ;
		if (!is_full(p))
			return (NULL);
		if (!p_sleep(p))
			break ;
		if (!print_action(THINKING, p, &p->m->mt.think, NULL))
			break ;
	}
	ghost_buster(p, 1);
	return (NULL);
}
