/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 19:44:50 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 12:43:19 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			start_draw(t_param *p)
{
	if (p->draw_start < 0)
		p->draw_start = 0;
	if (p->lvl_map[p->map_x][p->map_y] == '1' ||
		p->lvl_map[p->map_x][p->map_y] == '9')
		p->draw_start = -(p->line_height) / 2 + (HEIGHT - 100) / 2;
	else if (p->lvl_map[p->map_x][p->map_y] == '2')
		p->draw_start = -(p->line_height) + (HEIGHT - 100) / 2;
	else if (p->lvl_map[p->map_x][p->map_y] == '3')
		p->draw_start = -(p->line_height) * 2 + (HEIGHT - 100) / 2;
	else if (p->lvl_map[p->map_x][p->map_y] == '4')
		p->draw_start = -(p->line_height) * 3 + (HEIGHT - 100) / 2;
	else if (p->lvl_map[p->map_x][p->map_y] == '5')
		p->draw_start = -(p->line_height) * 4 + (HEIGHT - 100) / 2;
}

static void		draw_floor(t_param *p, int x, int y, char *pos)
{
	int		a;

	a = 0;
	if (p->furious == -1)
		a = 30;
	while (x <= WIDTH)
	{
		while (y < HEIGHT - 100)
		{
			pos = p->data + p->size_line * y + x * (p->bpp / 8);
			*pos = 0;
			*(pos + 1) = 40 - a;
			*(pos + 2) = 70;
			y++;
		}
		x++;
		y = (HEIGHT - 100) / 2;
	}
}

void			draw_sky(t_param *p, int x, int y)
{
	char	*pos;
	int		a;

	a = 0;
	if (p->furious == -1)
		a = 24;
	pos = p->data;
	while (x <= WIDTH)
	{
		while (y <= (HEIGHT - 100) / 2)
		{
			pos = p->data + p->size_line * y + x * (p->bpp / 8);
			*pos = 80 - a * 2;
			*(pos + 1) = 16 - a / 2;
			*(pos + 2) = 0;
			y++;
		}
		x++;
		y = 0;
	}
	draw_floor(p, 0, (HEIGHT - 100) / 2, pos);
}

static void		ft_pixel_to_image(t_param *p, int x, int y, long color)
{
	char	*pos;

	pos = p->data_i + y * p->size_line + x * (p->bpp / 8);
	pos[0] = color;
	pos[1] = color >> 8;
	pos[2] = color >> 16;
}

void			perm_interface(t_param *p, int x, int j)
{
	while (x++ < WIDTH)
		ft_pixel_to_image(p, x, j, 0x9933C1B1);
	x = 320;
	while (j++ < 100)
		ft_pixel_to_image(p, x, j, 0x0033C1B1);
	j = 25;
	while (x++ < 550)
		ft_pixel_to_image(p, x, j, 0x0033C1B1);
	j = 0;
	while (j++ < 100)
		ft_pixel_to_image(p, x, j, 0x0033C1B1);
	j = 70;
	x = 160;
	while (x++ < 242)
		ft_pixel_to_image(p, x, j, 0x00FF6633);
	while (j-- >= 58)
		ft_pixel_to_image(p, x, j, 0x00FF6633);
	while (x-- >= 160)
		ft_pixel_to_image(p, x, j, 0x00ff6633);
	while (j++ < 70)
		ft_pixel_to_image(p, x, j, 0x00FF6633);
}
