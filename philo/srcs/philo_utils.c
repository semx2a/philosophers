/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:34 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/28 16:16:17 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned int	chrono(t_time *t)
{
	long	current;
	long	begin;

	gettimeofday(&t->step, NULL);
	current = (t->step.tv_sec * 1000) + (t->step.tv_usec / 1000);
	begin = (t->start.tv_sec * 1000) + (t->start.tv_usec / 1000);
	return ((unsigned)(current - begin));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	r;

	i = 0;
	n = 1;
	r = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			n *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		r = r * 10 + (int)str[i] - 48;
		i++;
	}
	return (n * r);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str)
		while (str[len])
			len++;
	return (len);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}
