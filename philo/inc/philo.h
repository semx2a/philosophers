/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/10 19:00:29 by seozcan          ###   ########.fr       */
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

// 		type limits
# include <limits.h>

//		ERRORS
# define ERR			"Error\n"
# define ERR_DIGITS		"Error: only digits allowed.\n"
# define ERR_ARGS		"Error: only 4 or 5 arguments allowed.\n"
# define ERR_ALLOC		"Error: allocation failed.\n"
# define ERR_MUTEX		"Error: mutex init failed.\n"
# define ERR_PHILOS		"Error: philos init failed\n"
# define ERR_THREAD		"Error: thread creation failed\n"

//		PARAMETERS
# define MAX_THREADS	1024

//		MESSAGES
# define DEAD			"%u %i \033[0;31mdied\033[0m\n"
# define EATING			"%u %i is \033[0;33meating\033[0m\n"
# define FORK			"%u %i has taken a \033[0;34mfork\033[0m\n"
# define THINKING		"%u %i is \033[0;36mthinking\033[0m\n"
# define SLEEPING		"%u %i is \033[0;35msleeping\033[0m\n"
# define XPD_DEATH		"%u %i is \033[0;37mexpected to die\033[0m\n"

//		STRUCTURES
//		unsigned long == time in usec

typedef struct s_mutex
{
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*time;
	pthread_mutex_t	display;
	pthread_mutex_t	satiated;
	pthread_mutex_t	reaper;
	pthread_mutex_t	chrono;
}	t_mutex;

typedef struct s_philos
{
	int				philo_id;
	int				r_fork;
	int				l_fork;
	int				eat_counter;
	int				err;
	unsigned int	time2_die;
	unsigned int	time2_eat;
	unsigned int	time2_sleep;
	unsigned int	expected_death;
	unsigned int	offset;
	unsigned int	timestamp;
	struct s_main	*m;
}	t_philos;

typedef struct s_main
{
	int				i;
	int				j;
	int				philo_nb;
	int				ghost;	
	int				stock_limit;
	int				*done_eating;
	int				*err;
	int				end_of_service;
	long			data;
	pthread_t		*philosophers;
	struct timeval	bigbang;
	t_philos		*p;
	t_mutex			mt;
}	t_main;

//		philo_routine.c
void			*routine(void *p_data);

//		philo_init.c
int				init_params(t_main *m, int ac, char **av);

//		philo_threads.c
int				philosophers_init(t_main *m);
int				philosophers_join(t_main *m);
int				ecg(t_main *m);

//		philo_protagonists.c
//int				ghost_buster(t_philos *p);
int				mr_sandman(t_philos *p, unsigned int time);
int				waiter(t_philos *p, int val);

//		philo_rw.c
int				read_data(pthread_mutex_t *mu, int *data);
void			write_data(pthread_mutex_t *mu, int *data, int value,
					char instruction);
unsigned int	read_udata(pthread_mutex_t *mu, unsigned int *data);
void			write_udata(pthread_mutex_t *mu, unsigned int *data,
					unsigned int value,	char instruction);

//		philo_tools.c
unsigned int	chrono(pthread_mutex_t *m, struct timeval bigbang);
int				print_action(t_philos *p, char *str);

//		philo_utils.c
int				ft_isdigit(int c);
long			ft_atoli(const char *str);
void			ft_error(char *str);
size_t			ft_strlen(const char *str);

#endif