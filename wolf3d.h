/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 11:44:26 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/29 11:33:08 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define HEIGHT	675
# define WIDTH	1200
# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6
# define MOVESPEED 0.3
# define ROTSPEED 0.12
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
# include "./MinilibX/mlx.h"

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

typedef struct		s_draw
{
		int				map_x;
	int				map_y;
	int				hit;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	unsigned int			color;
}					t_draw;

/* color --> pos_x pos_y et step_x step_y */

typedef struct		s_param
{
	char			**lvl_map;
	char			*data;
	void			*mlx;
	void			*win;
	void			*img;
	int				bpp;
	int				size_line;
	int				endian;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			time;
	double			old_time;
	double			mv_speed;
	double			rot_sp;
	double			olddir_x;
	double			oldplane_x;
}					t_param;

/*
** Fonctions in key_mouse_wolf3d file
*/

int					key_function(int keycode, t_param *p);
int					mouse_function(int button, int x, int y, t_param *p);
int					ft_motion(int x, int y, t_param *p);

/*
** Fonctions in user_interface file
*/

void				user_interface(t_param *p, int x, int i, int j);

/*
** Fonctions in levels_wolf3d file
*/

void				error_wolf3d(char *c);
char				**loading_lvl(int nb_line, int fd, char *lvl_name);

/*
** Fonctions in loop_wolf3d file
*/

void				draw_wolf3d(t_param *p, int x);

/*
** Fonctions in loop_wolf3d file
*/

void				put_pixels(t_param *p, int x, int y, unsigned int color);

#endif
