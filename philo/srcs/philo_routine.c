/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:55:00 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/09 18:32:20 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_full(t_philos *p)
{	
	p->eat_counter++;
	if (p->eat_counter == p->n_eats)
		write_data(&p->m->mt.satiated, &p->m->done_eating, 1, '+');
	if (read_data(&p->m->mt.satiated, &p->m->done_eating)
		== read_data(&p->m->mt.satiated, &p->m->philo_nb))
		return (0);
	return (1);
}

int	p_sleep(t_philos *p)
{	
	if (!print_action(p, SLEEPING))
		return (0);
	if (!mr_sandman(p, p->time2_sleep))
		return (0);
	return (1);
}

int	think(t_philos *p)
{
	if (!print_action(p, THINKING))
		return (0);
	return (1);
}

int	eat(t_philos *p)
{
	while (read_data(&p->m->mt.platter, &p->m->platter[p->l_fork])
		&& read_data(&p->m->mt.platter, &p->m->platter[p->r_fork]))
		usleep(10);
	if (!platter(p, 1))
		return (0);
	if (!print_action(p, EATING))
	{	
		platter(p, 0);
		return (0);
	}
	if (!mr_sandman(p, p->time2_eat))
	{	
		platter(p, 0);
		return (0);
	}
	p->expected_death = p->timestamp + p->time2_die;
	platter(p, 0);
	return (1);
}

void	*routine(void *p_data)
{
	t_philos	*p;

	p = (t_philos *)p_data;
	p->expected_death = chrono(p->m->bigbang) + p->time2_die;
	if (p->philo_id % 2 == 0)
		if (!mr_sandman(p, p->offset))
			return (NULL);
	while (1)
	{
		p->err = eat(p);
		if (p->err == 0)
			break ;
		else
		{
			if (p->food_limit == 1 && !is_full(p))
				return (0);
			if (!p_sleep(p))
				return (0);
		}
		if (!think(p))
			break ;
	}
	return (NULL);
}
