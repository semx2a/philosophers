/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/09 17:27:20 by seozcan          ###   ########.fr       */
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
	int		i;
	int		j;
	int		k;
	int		fd;
	int		size;
	int		*arr;
	int		**tab;
	char	*str;
	char	**stab;
}	t_main;

#endif