/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_wolf3d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:03:00 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/27 16:43:14 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		key_function_2(int key, t_param *p)
{
	if (key == 124)
	{
		p->olddir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-(p->rot_sp)) - p->dir_y * sin(-(p->rot_sp));
		p->dir_y = p->olddir_x * sin(-(p->rot_sp)) + p->dir_y *
		cos(-(p->rot_sp));
		p->oldplane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-(p->rot_sp)) - p->plane_y *
			sin(-(p->rot_sp));
		p->plane_y = p->oldplane_x * sin(-(p->rot_sp)) + p->plane_y *
			cos(-(p->rot_sp));
	}
	if (key == 123)
	{
		p->olddir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(p->rot_sp) - p->dir_y * sin(p->rot_sp);
		p->dir_y = p->olddir_x * sin(p->rot_sp) + p->dir_y * cos(p->rot_sp);
		p->oldplane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(p->rot_sp) - p->plane_y * sin(p->rot_sp);
		p->plane_y = p->oldplane_x * sin(p->rot_sp) + p->plane_y * cos(p->rot_sp);
	}
}

int				key_function(int key, t_param *p)
{
	if (key == 53)
	{
		ft_putendl("\033[31mGaming session finished");
		ft_putendl("\033[36mThank you so much for to playing my game !");
		exit(EXIT_SUCCESS);
	}
	if (key == 126)
	{
		if (p->lvl_map[(int)(p->pos_x + p->dir_x * p->mv_speed)]
			[(int)(p->pos_y)] == '0')
			p->pos_x += p->dir_x * p->mv_speed;
		if (p->lvl_map[(int)(p->pos_x)]
			[(int)(p->pos_y + p->dir_y * p->mv_speed)] == '0')
			p->pos_y += p->dir_y * p->mv_speed;
	}
	if (key == 125)
	{
		if (p->lvl_map[(int)(p->pos_x - p->dir_x * p->mv_speed)]
			[(int)(p->pos_y)] == '0')
			p->pos_x -= p->dir_x * p->mv_speed;
		if (p->lvl_map[(int)(p->pos_x)]
			[(int)(p->pos_y - p->dir_y * p->mv_speed)] == '0')
			p->pos_y -= p->dir_y * p->mv_speed;
	}
	key_function_2(key, p);
	draw_wolf3d(p, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	user_interface(p, 0, 0, 0);
	return (0);
}

int				mouse_function(int button, int x, int y, t_param *p)
{
	if (x == 0 && p->time == 0)
		y++;
	if (button == 1 || button == 5)
	{
/*		p->zoom *= 9 / 9.5;
		p->pos.r += ((y / 4 - (WIDTH / 8 - 30)) * 0.0001) * p->zoom / 0.0002;
		p->pos.i += ((x / 4 - (HEIGHT / 8 - 30)) * 0.0001) * p->zoom / 0.0002;
*/	}
/*	if (button == 2 || button == 4)
	{
		p->zoom *= 10 / 9.5;
		p->pos.r += ((y / 4 - (WIDTH / 8 - 30)) * 0.0001) * p->zoom / 0.0002;
		p->pos.i += ((x / 4 - (HEIGHT / 8 - 30)) * 0.0001) * p->zoom / 0.0002;
	}
*/	draw_wolf3d(p, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	user_interface(p, 0, 0, 0);
	return (0);
}


int				ft_motion(int x, int y, t_param *p)
{
	if (x >= 0 && y >= 0 && x <= WIDTH && y <= HEIGHT)
	{
/*		p->z.r = ((double)x / (double)WIDTH * 4 - 2) / 2;
		p->z.i = ((double)y / (double)HEIGHT * 4 - 2) / 2;
*/		draw_wolf3d(p, 0);
		mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
		user_interface(p, 0, 0, 0);
	}
	return (0);
}

