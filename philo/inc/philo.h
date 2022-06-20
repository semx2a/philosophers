/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/20 23:18:06 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

//		LIBRARIES
//		memset
# include <string.h>

//		read, write, exit, usleep
# include <unistd.h>

//		malloc, free
# include <stdlib.h>

//		filedes, printf
# include <stdio.h>

//		gettimeofday
# include <sys/time.h>

//		pthread*
# include <pthread.h>

//		int/pointer cast
# include <stdint.h>

//		ERRORS
# define ERR			"Error"
# define ERR_DIGITS		"Error: only digits allowed."
# define ERR_ARGS		"Error: only 4 or 5 arguments allowed."
# define ERR_MAXINT		"Error: MAXINT detected."
# define ERR_THREAD		"Philosopher died on inception."

//		PARAMETERS
# define INT_MIN		-2147483648
# define INT_MAX		2147483647
# define MAX_THREADS	1024

//		STRUCTURES

typedef struct s_mutex
{
	int				data;
	pthread_mutex_t mutex;
} 	t_mutex;

typedef struct s_time
{	
	float			*time;
	struct timeval	start;
	struct timeval	end;
}	t_time;

typedef struct s_main
{
	int				i;
	int				j;
	int				*ret;
	int				philo_nb;
	int				forks;
	int				n_eats;
	unsigned int	time_2die;
	unsigned int	time_2eat;
	unsigned int	time_2sleep;
	pthread_t		*philosophers;
}	t_main;

//		main.c
void	*routine(void *p_data);

//		philo_init.c
int		init_params(t_main *m, int ac, char **av);

//		philo_utils.c
float	time_diff(struct timeval *start, struct timeval *end);
int		ft_isdigit(int c);
long	ft_atoli(const char *str);
size_t	ft_strlen(const char *str);
void	ft_error(char *str);

#endif