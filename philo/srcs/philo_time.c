/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:05:20 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/28 12:49:17 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	time_diff(t_time *t)
{
	gettimeofday(&t->step, NULL);
	return (((t->step.tv_sec - t->start.tv_sec)
			+ (t->step.tv_usec - t->start.tv_usec)) / 1000);
}
