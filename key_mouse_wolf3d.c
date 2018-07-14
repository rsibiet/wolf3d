/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_wolf3d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:03:00 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 14:08:50 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		key_function_4(int key, t_param *p)
{
	if (key == 53)
	{
		ft_strdel(&p->lvl_nb);
		ft_strdel_del(&p->lvl_map);
		mlx_destroy_image(p->mlx, p->img[0]);
		mlx_destroy_image(p->mlx, p->img[1]);
		mlx_destroy_window(p->mlx, p->win);
		p->mlx = NULL;
		p->img[0] = NULL;
		p->img[1] = NULL;
		ft_putendl("\033[31mGaming session finished");
		ft_putendl("\033[36mThank you so much for to playing my game !");
		exit(EXIT_SUCCESS);
	}
	if (key == 49 && p->drug_mode == 0 && p->time_furious == 5 && p->pos_x > 3)
	{
		if (p->mv_speed != 1.0)
			p->mv_speed = 1.0;
		else
			p->mv_speed = 0.3;
		p->furious *= -1;
	}
}

static void		key_function_3(int key, t_param *p)
{
	if (key == 82 && p->mv_speed != 1.0)
	{
		if (p->drug_mode == 0)
			p->drug_mode = 245;
		else if (p->drug_mode == 245)
		{
			p->drug_mode = 253;
			p->mv_speed = 0.1;
		}
		else
		{
			p->drug_mode = 0;
			p->mv_speed = 0.3;
		}
	}
	key_function_4(key, p);
}

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
		p->plane_y = p->oldplane_x * sin(p->rot_sp) + p->plane_y *
			cos(p->rot_sp);
	}
	key_function_3(key, p);
}

int				key_function(int key, t_param *p)
{
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
	if (p->game_over == 0)
	{
		mlx_put_image_to_window(p->mlx, p->win, p->img[0], 0, 0);
		user_interface(p, 8, HEIGHT - 100);
	}
	return (0);
}
