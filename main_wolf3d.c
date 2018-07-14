/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wolf3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 11:49:54 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 14:09:48 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			expose_hook(t_param *p)
{
	char		c;

	if (p->pos_x <= 3 && p->pos_y <= 3 && p->lvl_nb[0] != '3')
	{
		p->timer += 90;
		p->pos_x = 48;
		p->pos_y = 3;
		c = p->lvl_nb[0] + 1;
		ft_strdel(&p->lvl_nb);
		ft_strdel_del(&p->lvl_map);
		p->lvl_nb = ft_strnew(1);
		p->lvl_nb[0] = c;
		p->lvl_map = loading_lvl(0, 0, p->lvl_nb, p);
	}
	else if (p->pos_x <= 3 && p->pos_y <= 3 && p->lvl_nb[0] == '3')
		ft_winner(p, 0, 0);
	else if (p->game_over == 0)
	{
		draw_wolf3d(p, 0);
		mlx_put_image_to_window(p->mlx, p->win, p->img[1], 0, HEIGHT - 100);
		mlx_put_image_to_window(p->mlx, p->win, p->img[0], 0, 0);
		user_interface(p, 8, HEIGHT - 100);
	}
	return (0);
}

static void			init_param_2(t_param *p)
{
	time_t		*t;

	t = NULL;
	p->timer = 120;
	p->step_y = 0;
	p->mv_speed = MOVESPEED;
	p->rot_sp = ROTSPEED;
	p->olddir_x = 0;
	p->oldplane_x = 0;
	p->side = 0;
	p->line_height = 0;
	p->draw_start = 0;
	p->draw_end = 0;
	p->color = 0;
	p->drug_mode = 0;
	p->game_over = 0;
	p->memo_t = time(t);
	p->furious = 1;
	p->tp_furious = 1;
	p->time_furious = 5;
	p->img[0] = NULL;
	p->img[1] = NULL;
}

static t_param		init_param(void)
{
	t_param		p;

	p.lvl_nb = ft_strdup("1");
	p.lvl_map = NULL;
	p.lvl_map = loading_lvl(0, 0, p.lvl_nb, &p);
	p.data = NULL;
	p.data_i = NULL;
	p.mlx = NULL;
	p.win = NULL;
	p.bpp = 0;
	p.size_line = 0;
	p.endian = 0;
	p.pos_x = 98;
	p.pos_y = 3;
	p.dir_x = -1;
	p.dir_y = 0;
	p.plane_x = 0;
	p.plane_y = 0.66;
	init_param_2(&p);
	p.map_x = 0;
	p.map_y = 0;
	p.hit = 0;
	p.step_x = 0;
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
	if ((p.mlx = mlx_init()) == NULL)
		ft_error("mlx_init failed.", &p);
	if ((p.win = mlx_new_window(p.mlx, WIDTH, HEIGHT, "wolf3d")) == NULL)
		ft_error("mlx_new_window failed.", &p);
	if ((p.img[0] = mlx_new_image(p.mlx, WIDTH, HEIGHT - 100)) == NULL)
		ft_error("mlx_new_image failed.", &p);
	if ((p.img[1] = mlx_new_image(p.mlx, WIDTH, 100)) == NULL)
		ft_error("mlx_new_image failed.", &p);
	p.data = mlx_get_data_addr(p.img[0], &p.bpp, &p.size_line, &p.endian);
	p.data_i = mlx_get_data_addr(p.img[1], &p.bpp, &p.size_line, &p.endian);
	perm_interface(&p, 0, 0);
	mlx_expose_hook(p.win, expose_hook, &p);
	mlx_hook(p.win, 2, 1, key_function, &p);
	mlx_loop_hook(p.mlx, expose_hook, &p);
	mlx_loop(p.mlx);
	return (0);
}
