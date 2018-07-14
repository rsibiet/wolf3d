/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_wolf3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:38:32 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 12:32:16 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		define_step(t_ray *ray, t_param *p)
{
	if (ray->dir_x < 0)
	{
		p->step_x = -1;
		ray->side_dist_x = (ray->pos_x - p->map_x) * ray->delta_dist_x;
	}
	else
	{
		p->step_x = 1;
		ray->side_dist_x = (p->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		p->step_y = -1;
		ray->side_dist_y = (ray->pos_y - p->map_y) * ray->delta_dist_y;
	}
	else
	{
		p->step_y = 1;
		ray->side_dist_y = (p->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void		perform_dda(t_ray *ray, t_param *p)
{
	while (p->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			p->map_x += p->step_x;
			p->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			p->map_y += p->step_y;
			p->side = 1;
		}
		if (p->lvl_map[p->map_x][p->map_y] > '0')
			p->hit = 1;
	}
	if (p->side == 0)
		ray->perp_wall_dist = (p->map_x - ray->pos_x + (1 - p->step_x) / 2) /
			ray->dir_x;
	else
		ray->perp_wall_dist = (p->map_y - ray->pos_y + (1 - p->step_y) / 2) /
			ray->dir_y;
}

static void		pixel_fill_2(t_param *p)
{
	if (p->lvl_map[p->map_x][p->map_y] >= '1' &&
		p->lvl_map[p->map_x][p->map_y] < '9' && p->line_height >= 32)
	{
		if (p->side == 1)
		{
			if (p->step_y == 1)
				p->color = 255 * 256 - 7136 / p->line_height * 256;
			else
				p->color = 255 * 256 * 256 - 7136 / p->line_height * 256 * 256;
		}
		else
		{
			if (p->step_x == 1)
				p->color = 255 * 256 + 255 * 256 * 256 -
					7136 / p->line_height * (256 * 256 + 256);
			else
				p->color = 255 - 7136 / p->line_height;
		}
	}
	else if (p->lvl_map[p->map_x][p->map_y] == '9')
		p->color = mlx_get_color_value(p->mlx, 255 + 51 * 256 + 204 * 65536);
}

static void		pixel_fill(t_ray *ray, t_param *p)
{
	start_draw(p);
	p->line_height = (int)((HEIGHT - 100) / ray->perp_wall_dist);
	p->draw_end = p->line_height / 2 + (HEIGHT - 100) / 2;
	if (p->draw_end >= HEIGHT - 100)
		p->draw_end = (HEIGHT - 100) - 1;
	if (p->lvl_map[p->map_x][p->map_y] >= '1' &&
		p->lvl_map[p->map_x][p->map_y] < '9' && p->line_height < 32)
	{
		if (p->side == 1)
		{
			if (p->step_y == 1)
				p->color = 32 * 256;
			else
				p->color = 32 * 256 * 256;
		}
		else
		{
			if (p->step_x == 1)
				p->color = 32 * 256 + 32 * 256 * 256;
			else
				p->color = 32;
		}
	}
	pixel_fill_2(p);
}

void			draw_wolf3d(t_param *p, int x)
{
	t_ray		ray;

	draw_sky(p, 0, 0);
	while (x < WIDTH)
	{
		ray.camera_x = 2 * x / (double)(WIDTH) - 1;
		ray.pos_x = p->pos_x;
		ray.pos_y = p->pos_y;
		ray.dir_x = p->dir_x + p->plane_x * ray.camera_x;
		ray.dir_y = p->dir_y + p->plane_y * ray.camera_x;
		p->map_x = (int)(ray.pos_x);
		p->map_y = (int)(ray.pos_y);
		ray.delta_dist_x = sqrt(1 + (ray.dir_y * ray.dir_y) /
			(ray.dir_x * ray.dir_x));
		ray.delta_dist_y = sqrt(1 + (ray.dir_x * ray.dir_x) /
			(ray.dir_y * ray.dir_y));
		p->hit = 0;
		define_step(&ray, p);
		perform_dda(&ray, p);
		pixel_fill(&ray, p);
		draw_line(p, p->draw_start, x);
		x++;
	}
}
