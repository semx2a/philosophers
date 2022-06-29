/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:38:34 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/28 13:10:49 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long unsigned	ft_atolu(const char *str)
{
	long unsigned	i;
	long unsigned	r;

	i = 0;
	r = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (ft_isdigit(str[i]))
	{
		r = r * 10 + (long unsigned)(str[i] - 48);
		i++;
	}
	return (r);
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
