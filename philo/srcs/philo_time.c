/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/30 16:34:36 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

suseconds_t	abs_usec(suseconds_t start, suseconds_t step)
{
	if (start > step)
		return (start - step);
	return (step - start);
}

unsigned long	time_diff(t_time *t)
{
	gettimeofday(&t->step, NULL);
	return ((unsigned long)((t->step.tv_sec - t->start.tv_sec)
		+ abs_usec(t->start.tv_usec, t->step.tv_usec)) / 1000);
}
