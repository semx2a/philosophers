/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/15 17:59:51 by seozcan          ###   ########.fr       */
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
# define ERR_MUTEX		"Error: mutex init failed.\n"
# define ERR_PHILOS		"Error: philos init failed\n"
# define ERR_THREAD		"Error: thread creation failed\n"

//		PARAMETERS
# define INT_MAX		2147483647
# define MAX_THREADS	1024

//		MESSAGES
# define DEAD			"%lu %lu died\n"
# define EATING			"%lu %lu is eating\n"
# define FORK			"%lu %lu has taken a fork\n"
# define THINKING		"%lu %lu is thinking\n"
# define SLEEPING		"%lu %lu is sleeping\n"

//		STRUCTURES
//		unsigned long == time in usec
typedef struct s_time
{
	unsigned long	time2_die;
	unsigned long	time2_eat;
	unsigned long	time2_sleep;
	struct timeval	start;
	struct timeval	step;
}	t_time;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	sleep;
	pthread_mutex_t	think;
	pthread_mutex_t	display;
	pthread_mutex_t	satiated;
	pthread_mutex_t	reaper;
}	t_mutex;

typedef struct s_philos
{
	unsigned long	philo_id;
	unsigned long	r_fork;
	unsigned long	l_fork;
	unsigned long	red_tape;
	unsigned long	n_eats;
	unsigned long	eat_counter;
	unsigned long	timestamp;
	struct s_main	*m;
}	t_philos;

typedef struct s_main
{
	size_t			i;
	size_t			j;
	int				*err;
	int				food_limit;
	int				ghost;
	unsigned long	philo_nb;
	unsigned long	done_eating;
	pthread_t		*philosophers;
	t_philos		*p;
	t_mutex			mt;
	t_time			t;
}	t_main;

//		philo_routine.c
void			*routine(void *p_data);

//		philo_threads.c
int				philosophers_init(t_main *m);
int				philosophers_detach(t_main *m);
int				philosophers_join(t_main *m);

//		philo_tools.c
unsigned long	chrono(t_time *t);
void			print_action(char *str, t_philos *p);
void			ft_flush(t_main *m);

//		philo_init.c
int				init_params(t_main *m, int ac, char **av);

//		philo_utils.c
int				ft_isdigit(int c);
unsigned long	ft_atolu(const char *str);
size_t			ft_strlen(const char *str);
void			ft_error(char *str);

#endif