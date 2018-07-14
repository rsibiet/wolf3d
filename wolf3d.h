/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 11:44:26 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 14:09:57 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define HEIGHT	900
# define WIDTH	1600
# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6
# define MOVESPEED 0.3
# define ROTSPEED 0.10
# define COLORA 16724838
# define COLORB 3394713
# define COLORC 16777011
# define COLORD 16750899
# define RED  16711680
# define GREEN  65280
# define YELLOW  16776960
# define BLUE  255

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <sys/time.h>

typedef struct		s_ray
{
	double			camera_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
}					t_ray;

typedef struct		s_param
{
	char			*lvl_nb;
	char			**lvl_map;
	char			*data;
	char			*data_i;
	void			*mlx;
	void			*win;
	void			*img[2];
	int				bpp;
	int				size_line;
	int				endian;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			mv_speed;
	double			rot_sp;
	double			olddir_x;
	double			oldplane_x;
	int				map_x;
	int				map_y;
	int				hit;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				drug_mode;
	int				furious;
	unsigned int	color;
	int				timer;
	int				memo_t;
	int				game_over;
	int				time_furious;
	int				tp_furious;
}					t_param;

/*
** Fonctions in key_mouse_wolf3d file
*/

int					key_function(int keycode, t_param *p);

/*
** Fonctions in user_interface file
*/

void				ft_winner(t_param *p, int x, int j);
void				user_interface(t_param *p, int x, int j);

/*
** Fonctions in perm_interface file
*/

void				start_draw(t_param *p);
void				draw_sky(t_param *p, int x, int y);
void				perm_interface(t_param *p, int x, int j);

/*
** Fonctions in levels_wolf3d file
*/

void				draw_line(t_param *p, int y_star, int x);
void				ft_error(char *c, t_param *p);
void				error_wolf3d(char *c, t_param *p);
char				**loading_lvl(int nb_line, int fd,
						char *lvl_name, t_param *p);

/*
** Fonctions in loop_wolf3d file
*/

void				draw_wolf3d(t_param *p, int x);

#endif
