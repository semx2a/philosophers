/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:24:36 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/09 17:45:44 by seozcan          ###   ########.fr       */
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
		-> int 		pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
		-> int 		pthread_detach(pthread_t thread);
		-> int		pthread_join(pthread_t thread, void **retval);
		-> int 		pthread_mutex_init(pthread_mutex_t *restrict mutex,
           			const pthread_mutexattr_t *restrict attr);
		-> int		pthread_mutex_destroy(pthread_mutex_t *mutex);
		-> int		pthread_mutex_lock(pthread_mutex_t *mutex);
		-> int		pthread_mutex_unlock(pthread_mutex_t *mutex);
*/

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	return (0);
}
