/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/13 21:01:23 by seozcan          ###   ########.fr       */
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

//		ERRORS
# define ERR			"Error"
# define ERR_DIGITS		"Error: only digits allowed."
# define ERR_ARGS		"Error: only 4 or 5 arguments allowed."
# define ERR_MAXINT		"Error: MAXINT detected."

//		PARAMETERS
# define INT_MIN		-2147483648
# define INT_MAX		2147483647

//		LINKED LISTS
//		nodes structure
typedef struct s_node
{
	void			*data;	
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_lst
{
	t_node	*head;
	t_node	*tail;
}	t_lst;

//		STRUCTURES
//		push_swap.c
typedef struct s_main
{
	int				i;
	int				j;
	int				k;
	int				fd;
	int				philo_nb;
	int				time_2die;
	int				time_2eat;
	int				time_2sleep;
	int				u_eats;
	int				size;
	int				*arr;
	int				**tab;
	char			*str;
	char			**stab;	
	struct timeval	start;
	struct timeval	end;
}	t_main;

//		philo_init.c
int		init_params(t_main *m, int ac, char **av);

//		philo_utils.c
float	time_diff(struct timeval *start, struct timeval *end);
int		ft_isdigit(int c);
long	ft_atoli(const char *str);
size_t	ft_strlen(const char *str);
void	ft_error(char *str);

#endif