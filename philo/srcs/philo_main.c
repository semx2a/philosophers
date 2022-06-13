/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:24:36 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/13 21:22:41 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		PHILOSOPHERS

		authorized functions:
		-> void		*memset(void *s, int c, size_t n);
		-> int		printf(const char *format, ...);
		-> void		*malloc(size_t size);
		-> void		free(void *ptr);
		-> ssize_t	write(int fd, const void *buf, size_t count);
		-> int		usleep(useconds_t usec);
		-> int 		gettimeofday(struct timeval *tv, struct timezone *tz);

		thread functions:
		-> int 		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
		-> int 		pthread_detach(pthread_t thread);
		-> int		pthread_join(pthread_t thread, void **retval);
		-> int 		pthread_mutex_init(pthread_mutex_t *restrict mutex,	const pthread_mutexattr_t *restrict attr);
		-> int		pthread_mutex_destroy(pthread_mutex_t *mutex);
		-> int		pthread_mutex_lock(pthread_mutex_t *mutex);
		-> int		pthread_mutex_unlock(pthread_mutex_t *mutex);

		args:
		2 ->		number_of_philosophers
		3 ->		time_to_die 
		4 ->		time_to_eat
		5 ->		time_to_sleep
		6 -> 		[optional] number_of_times_each_philosopher_must_eat

		A faire:
		-> ft_usleep pour gerer les usleep de maniere fine
		-> un thread join par thread create dans le main thread
		-> verifier les mutex deadlock avec [valgrind --tool=helgrind] 
*/

#include "../inc/philo.h"

//void	philosopher(t_main *m)
//{
//	pthread_t	philosopher;
//
//	pthread_create(philosopher, NULL, *(f)(loop_function), NULL);
//
//}

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
//	gettimeofday(&m.start, 0);
//	philosopher(&m);
//	gettimeofday(&m.end, 0);
//	printf("time spent = %0.8f\n", time_diff(&m.start, &m.end));
	return (0);
}
