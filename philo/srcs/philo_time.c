/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/07 17:20:24 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	time_diff(t_time *t)
{
	long	current;
	long	begin;

	gettimeofday(&t->step, NULL);
	current = (t->step.tv_sec * 1000) + (t->step.tv_usec / 1000);
	begin = (t->start.tv_sec * 1000) + (t->start.tv_usec / 1000);
	return (current - begin);
}
