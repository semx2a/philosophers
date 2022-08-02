/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/08/02 21:33:08 by seozcan          ###   ########.fr       */
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
# define DEAD			"%u %i \033[0;31mdied\033[0m\n"
# define EATING			"%u %i is \033[0;33meating\033[0m\n"
# define FORK			"%u %i has taken a \033[0;34mfork\033[0m\n"
# define THINKING		"%u %i is \033[0;36mthinking\033[0m\n"
# define SLEEPING		"%u %i is \033[0;35msleeping\033[0m\n"

//		STRUCTURES
//		unsigned long == time in usec

typedef struct s_mutex
{
	pthread_mutex_t	*waiter;
	pthread_mutex_t	display;
	pthread_mutex_t	satiated;
	pthread_mutex_t	reaper;
}	t_mutex;

typedef struct s_philos
{
	int				philo_id;
	int				r_fork;
	int				l_fork;
	int				n_eats;	
	int				eat_counter;
	int				food_limit;
	int				err;
	unsigned int	time2_die;
	unsigned int	expected_death;
	unsigned int	time2_eat;
	unsigned int	time2_sleep;
	unsigned int	timestamp;
	struct s_main	*m;
}	t_philos;

typedef struct s_main
{
	int				i;
	int				j;
	int				philo_nb;
	int				*err;
	int				start;
	int				ghost;
	int				done_eating;
	pthread_t		*philosophers;
	struct timeval	bigbang;
	t_philos		*p;
	t_mutex			mt;
}	t_main;

//		philo_routine.c
void			*routine(void *p_data);

//		philo_threads.c
int				philosophers_init(t_main *m);
int				philosophers_detach(t_main *m);
int				philosophers_join(t_main *m);

//		philo_tools.c
int				print_action(t_philos *p, char *str);
int				ghost_buster(t_philos *p);
void			ft_flush(t_main *m);

//		philo_mutexes.c
int				read_data(pthread_mutex_t *mu, int *data);
void			write_data(pthread_mutex_t *mu, int *data, int value,
					char instruction);
int				waiter(t_philos *p, int (*f)(pthread_mutex_t *), char *str);

//		philo_init.c
int				init_params(t_main *m, int ac, char **av);

//		philo_utils.c
unsigned int	chrono(struct timeval bigbang);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			ft_error(char *str);

#endif