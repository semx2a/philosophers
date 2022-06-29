/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/28 13:16:32 by seozcan          ###   ########.fr       */
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
# define ERR			"Error\n"
# define ERR_DIGITS		"Error: only digits allowed.\n"
# define ERR_ARGS		"Error: only 4 or 5 arguments allowed.\n"
# define ERR_MAXINT		"Error: MAXINT detected.\n"

//		PARAMETERS
# define INT_MAX		2147483647
# define MAX_THREADS	1024

//		MESSAGES
# define DEAD			"%lu philosopher %lu died\n"
# define EATING			"%lu philosopher %lu is eating\n"
# define FORK			"%lu philosopher %lu has taken a fork\n"
# define THINKING		"%lu philosopher %lu is thinking\n"
# define SLEEPING		"%lu philosopher %lu is thinking\n"

//		STRUCTURES
typedef struct s_time
{
	useconds_t		time2_d;
	useconds_t		time2_e;
	useconds_t		time2_s;	
	struct timeval	start;
	struct timeval	step;
}	t_time;

typedef struct s_mutex
{
	long unsigned int	data;
	pthread_mutex_t		mutex;
}	t_mutex;

typedef struct s_philos
{
	long unsigned	philo_nb;
	long unsigned	philo_id;
	long unsigned	forks;
	long unsigned	n_eats;
	long unsigned	time_2die;
	long unsigned	time_2eat;
	long unsigned	time_2sleep;
	pthread_t		*philosophers;
}	t_philos;

typedef struct s_main
{
	int				i;
	int				j;
	int				*ret;
	t_philos		p;
	t_mutex			mt;
	t_time			t;
}	t_main;

//		philo_routine.c
void			*routine(void *p_data);

//		philo_times.c
long			time_diff(t_time *t);

//		philo_init.c
int				init_params(t_main *m, int ac, char **av);

//		philo_utils.c
int				ft_isdigit(int c);
long unsigned	ft_atolu(const char *str);
size_t			ft_strlen(const char *str);
void			ft_error(char *str);

#endif