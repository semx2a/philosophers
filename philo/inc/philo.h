/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/30 17:18:54 by seozcan          ###   ########.fr       */
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
# define ERR_ALLOC		"Error: allocation failed.\n"
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
	useconds_t		time2_die;
	useconds_t		time2_eat;
	useconds_t		time2_sleep;	
	struct timeval	start;
	struct timeval	step;
}	t_time;

typedef struct s_mutex
{
	unsigned long	data;
	pthread_mutex_t	mutex;
	pthread_mutex_t	forks;
}	t_mutex;

typedef struct s_philos
{
	unsigned long	philo_nb;
	unsigned long	philo_id;
	unsigned long	forks;
	unsigned long	n_eats;
	pthread_t		*philosophers;
}	t_philos;

typedef struct s_main
{
	int			i;
	int			j;
	int			*err;
	t_philos	p;
	t_mutex		mt;
	t_time		t;
}	t_main;

//		philo_routine.c
void			*routine(void *p_data);

//		philo_times.c
unsigned long	time_diff(t_time *t);

//		philo_init.c
int				init_params(t_main *m, int ac, char **av);

//		philo_utils.c
int				ft_isdigit(int c);
unsigned long	ft_atolu(const char *str);
size_t			ft_strlen(const char *str);
void			ft_error(char *str);
void			*xmalloc(size_t size);

#endif