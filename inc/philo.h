/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:14:19 by seozcan           #+#    #+#             */
/*   Updated: 2022/06/08 20:04:37 by seozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

//		LIBRARIES
//		memset
# include <string.h>

//		read, write, exit, usleep,
# include <unistd.h>

//		malloc, free
# include <stdlib.h>

//		filedes, printf
# include <stdio.h>

//		gettimeofday
# include <sys/time.h>

//		ERRORS
# define ERR			"Error"
# define ERR_FILE		"Wrong file format. Exiting."
# define ERR_READ		"Cannot read file."

//		WINDOW SIZE
# define WIDTH			1600
# define HEIGHT			1200

//		PARAMETERS
# define INT_MIN		-2147483648
# define INT_MAX		2147483647
# define BUFFER_SIZE	5120

//		ANGLES
# define DIA			0.46373398
# define ISO			0.523599

//		KEYCODES
# define ARROW_LEFT		65361
# define ARROW_UP		65362
# define ARROW_RIGHT	65363
# define ARROW_DOWN		65364
# define PLUS_NUM		65451
# define PLUS_KEY		65505
# define MINUS_NUM		65453
# define MINUS_KEY		45
# define ZERO_KEY		48
# define ZERO_NUM		65438

//		MOUSE_BUTTONS
# define WHEEL_UP		5
# define WHEEL_DOWN		4
# define WHEEL_CLICK	2
# define RIGHT_CLICK	3
# define LEFT_CLICK		1

//		LINKED LISTS
//		nodes structure
typedef struct s_node
{	
	int				x;
	int				y;
	int				z;
	unsigned int	color;
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
	int		x;
	int		y;
	int		z;
	int		fd;
	int		size;
	int		*arr;
	int		**tab;
	char	*str;
	char	**stab;
}	t_main;

typedef struct s_map
{	
	int		xinc;
	int		yinc;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		ex;
	int		ey;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
}	t_map;

typedef struct s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*ptr;
	char	*addr;
	int		bpp;
	int		seglen;
	int		width;
	int		height;
	int		zoom;
	int		center[2];
	int		x_offset;
	int		y_offset;
	float	z_div;
	int		endian;	
	t_lst	*matrix;
	t_node	*tmp_a;
	t_node	*tmp_b;
	t_node	*hold;
}	t_img;

//		fdf_projections.c
int		render(t_img *img);

//		fdf_parse.c
void	map_alloc(char **av, t_main *m, t_img *img);

//		fdf_controls.c
void	controls(t_img *img);

//		fdf_mods.c
void	ft_z_div(int keycode, t_img *img);
void	ft_move(int keycode, t_img *img);
void	ft_zoom(int button, t_img *img);

//		fdf_init.c
void	img_init(t_img *img);
void	window_init(t_img *img);
void	cam_init(t_img *img);
void	reset(t_img *img);

//		fdf_bresenham.c
void	drawline_y(t_map *map, t_img *img, t_node *ext1);
void	drawline_x(t_map *map, t_img *img, t_node *ext1);
void	put_pixel(t_img *img, int x, int y, int color);

//		fdf_utils.c
int		ft_min(int a, int b);
void	destroy(t_img *img);
void	free_and_exit(void *ptr);

//		fdf_print.c
void	print_lst(t_lst *matrix);
void	print_node(t_node *node);
void	print_address(t_lst *stack);

//		fdf_list.c
int		lst_size(t_lst *lst);
void	init_lst(t_img *img);
void	put_back(t_lst *lst, int x, int y, int z);
void	free_lst(t_lst *lst);

//		get_next_line.c
char	*get_next_line(int fd);
char	*set_head(char *head);
char	*get_line(char *ln, char *head);
char	*append_lines(int fd, char *buff, char *head);

//		get_next_line_utils.c
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_gnl(const char *str);

#endif
