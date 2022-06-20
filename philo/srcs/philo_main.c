/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:24:36 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/20 23:00:46 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		PHILOSOPHERS

		AUTHORIZED FUNCTIONS:
		-> void		*memset(void *s, int c, size_t n);
		-> int		printf(const char *format, ...);
		-> void		*malloc(size_t size);
		-> void		free(void *ptr);
		-> ssize_t	write(int fd, const void *buf, size_t count);
		-> int		usleep(useconds_t usec);
		-> int 		gettimeofday(struct timeval *tv, struct timezone *tz);

		THREAD FUNCTIONS:
		-> int 		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
		-> int 		pthread_detach(pthread_t thread);
		-> int		pthread_join(pthread_t thread, void **retval);
		
		MUTEX FUNCTIONS:
		-> int 		pthread_mutex_init(pthread_mutex_t *restrict mutex,	const pthread_mutexattr_t *restrict attr);
		-> int		pthread_mutex_destroy(pthread_mutex_t *mutex);
		-> int		pthread_mutex_lock(pthread_mutex_t *mutex);
		-> int		pthread_mutex_unlock(pthread_mutex_t *mutex);

		ARGS:
		av[1]		number_of_philosophers
		av[2]		time_to_die 
		av[3]		time_to_eat
		av[4]		time_to_sleep
		av[5] 		[optional] number_of_times_each_philosopher_must_eat

		TO DO LIST:
		-> ft_usleep pour gerer les usleep de maniere fine
		-> un thread join par thread create dans le main thread
		-> verifier les mutex deadlock avec [valgrind --tool=helgrind] 	
		
		TO IMPLEMENT:
		printf("%0.8f : philosopher %d has taken a fork", time_diff(&m.start, &m.end), philo_id);
		printf("%0.8f : philosopher %d is eating", time_diff(&m.start, &m.end), philo_id);
		printf("%0.8f : philosopher %d is sleeping", time_diff(&m.start, &m.end), philo_id);
		printf("%0.8f : philosopher %d is thinking", time_diff(&m.start, &m.end), philo_id);
		printf("%0.8f : philosopher %d died", time_diff(&m.start, &m.end), philo_id);
*/

#include "../inc/philo.h"

void	*routine(void *p_data)
{
	printf("philosopher #%ld\n", (intptr_t)p_data);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main	m;

	m = (t_main){0};
	if (ac < 5 || ac > 6)
	{
		ft_error(ERR_ARGS);
		return (0);
	}
	if (!init_params(&m, ac, av))
		return (0);
	while (m.i < m.philo_nb)
	{
		m.ret[m.i] = pthread_create(&m.philosophers[m.i], NULL,
				&routine, (void*)(intptr_t)m.i);
		if (m.ret[m.i] != 0)
		{
			ft_error(ERR_THREAD);
			return (0);
		}
		m.i++;
	}
	m.i = 0;
	while (m.i < m.philo_nb)
	{
		if (pthread_join(m.philosophers[m.i], 
			(void *)(intptr_t)m.ret[m.i]) != 0)
			return (0);
		m.i++;
	}
	free(m.philosophers);
	free(m.ret);
	return (0);
}
