/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/07/22 22:48:27 by seozcan          ###   ########.fr       */
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

//		error numbers
# include <errno.h>

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
# define DEAD			"%lu %lu \033[0;31mdied\033[0m\n"
# define EATING			"%lu %lu is \033[0;33meating\033[0m\n"
# define FORK			"%lu %lu has taken a \033[0;34mfork\033[0m\n"
# define THINKING		"%lu %lu is \033[0;36mthinking\033[0m\n"
# define SLEEPING		"%lu %lu is \033[0;35msleeping\033[0m\n"

//		STRUCTURES
//		unsigned long == time in usec
typedef struct s_time
{
	struct timeval	start;
	struct timeval	step;
}	t_time;

typedef struct s_mutex
{
	pthread_mutex_t	*waiter;
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
	unsigned long	time2_die;
	unsigned long	time2_eat;
	unsigned long	time2_sleep;
	unsigned long	timestamp;
	unsigned long	n_eats;	
	unsigned long	eat_counter;
	int				food_limit;
	struct s_main	*m;
}	t_philos;

typedef struct s_main
{
	size_t			i;
	size_t			j;
	int				*err;
	int				ghost;
	unsigned long	done_eating;
	unsigned long	philo_nb;
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
void			ft_flush(t_main *m);
int				print_action(char *s, t_philos *p, pthread_mutex_t *m1,
					pthread_mutex_t *m2);
int				ghost_buster(t_philos *p, int alert);

//		philo_init.c
int				init_params(t_main *m, int ac, char **av);

//		philo_utils.c
int				ft_isdigit(int c);
unsigned long	ft_atolu(const char *str);
size_t			ft_strlen(const char *str);
void			ft_error(char *str);

#endif