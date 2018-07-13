/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wolf3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 11:49:54 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/29 11:32:39 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			expose_hook(t_param *p)
{
	draw_wolf3d(p, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	user_interface(p, 0, 0, 0);
	return (0);
}

static void		init_param_2(t_param *p)
{
	p->mv_speed = MOVESPEED;
	p->rot_sp = ROTSPEED;
	p->olddir_x = 0;
	p->oldplane_x = 0;
}

static t_param		init_param(void)
{
	t_param		p;

	p.lvl_map = loading_lvl(0, 0, "level_1");
	p.data = NULL;
	p.mlx = NULL;
	p.win = NULL;
	p.img = NULL;
	p.bpp = 0;
	p.size_line = 0;
	p.endian = 0;
	p.pos_x = 22;
	p.pos_y = 12;
	p.dir_x = -1;
	p.dir_y = 0;
	p.plane_x = 0;
	p.plane_y = 0.66;
	p.time = 0;
	p.old_time = 0;
	init_param_2(&p);
	return (p);
}

int					main(int ac, char **av)
{
	t_param		p;

	p = init_param();
	if (ac != 1 || av == NULL)
	{
		ft_putendl_fd("\x1B[31mwolf3d: Too many arguments.", 2);
		ft_putendl_fd("\x1B[37mwolf3d need no argument.", 2);
		return (0);
	}
	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, WIDTH, HEIGHT, "wolf3d");
	p.img = mlx_new_image(p.mlx, WIDTH, HEIGHT);
	p.data = mlx_get_data_addr(p.img, &p.bpp, &p.size_line, &p.endian);
	mlx_expose_hook(p.win, expose_hook, &p);
	mlx_hook(p.win, 2, 1, key_function, &p);
	mlx_hook(p.win, MOTION_NOTIFY, PTR_MOTION_MASK, ft_motion, &p);
	mlx_mouse_hook(p.win, mouse_function, &p);
	mlx_loop(p.mlx);
	ft_strdel_void(&(p.mlx));
	ft_strdel_void(&(p.win));
	return (0);
}
