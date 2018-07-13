/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_wolf3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:38:32 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/29 11:34:10 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		define_step(t_ray *ray, t_draw *d)
{
	if (ray->dir_x < 0)
	{
		d->step_x = -1;
		ray->side_dist_x = (ray->pos_x - d->map_x) * ray->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		ray->side_dist_x = (d->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		d->step_y = -1;
		ray->side_dist_y = (ray->pos_y - d->map_y) * ray->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		ray->side_dist_y = (d->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void		perform_dda(t_ray *ray, t_param *p, t_draw *d)
{
	while (d->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (p->lvl_map[d->map_x][d->map_y] > '0')
			d->hit = 1;
	}
	if (d->side == 0)
		ray->perp_wall_dist = (d->map_x - ray->pos_x + (1 - d->step_x) / 2) /
			ray->dir_x;
	else
		ray->perp_wall_dist = (d->map_y - ray->pos_y + (1 - d->step_y) / 2) /
			ray->dir_y;
}

/*
void			put_pixel_text(t_env *e, int x, int y)
{
	char		*pixel;
	char		*text;
	int			i;

	i = -1;
	if ((x < e->img.width && y < e->img.height) && (x >= 0 && y >= 0))
	{
		pixel = e->img.data + y * e->img.sizeline + (e->img.bpp / 8) * x;
		if (t.name != 'p')
			text = t.data + e->texy * t.sizeline + (t.bpp / 8) * e->texx;
		else
			text = t.data + t.height * t.sizeline + (t.bpp / 8) * t.width;
		pixel[2] = text[2];
		pixel[1] = text[1];
		pixel[0] = text[0];

		pixel[2] = 0;
		pixel[1] = text[1];
		pixel[0] = text[0];
	}
}
*/
static void		pixel_fill(t_ray *ray, t_param *p, t_draw *d)
{
	void		*mlx_ptr;

	mlx_ptr = p->mlx;
	d->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	d->draw_start = -(d->line_height) / 2 + HEIGHT / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = d->line_height / 2 + HEIGHT / 2;
	if (d->draw_end >= HEIGHT)
		d->draw_end = HEIGHT - 1;
	if (p->lvl_map[d->map_x][d->map_y] == '1')
		d->color = mlx_get_color_value(mlx_ptr, 3000);
	/* define colors */
	if (d->side == 1)
		d->color = d->color / 2;
}

static void		draw_line(t_param *p, int y_start, int x, t_draw *d)
{
	y_start -= 1;
	while (++y_start < d->draw_end)
		put_pixels(p, x, y_start, d->color);
}

t_draw			init_d(void)
{
	t_draw		d;

	d.map_x = 0;
	d.map_y = 0;
	d.hit = 0;
	d.step_x = 0;
	d.step_y = 0;
	d.side = 0;
	d.line_height = 0;
	d.draw_start = 0;
	d.draw_end = 0;
	d.color = 0;
	return (d);
}

void			draw_wolf3d(t_param *p, int x)
{
	t_ray		ray;
	t_draw		d;
	char		*pos;
	int x_ = 0;
	int y = 0;

	while (x_ < WIDTH)
	{
		while (y < HEIGHT)
		{
			pos = p->data + p->size_line * y + x_ * (p->bpp / 8);
			*pos = 0;
			*(pos + 1) = 0;
			*(pos + 1) = 0;
			y++;
		}
		x_++;
		y = 0;
	}
	while (x < WIDTH)
	{
		d = init_d();
		ray.camera_x = 2 * x / (double)(WIDTH) - 1;
		ray.pos_x = p->pos_x;
		ray.pos_y = p->pos_y;
		ray.dir_x = p->dir_x + p->plane_x * ray.camera_x;
		ray.dir_y = p->dir_y + p->plane_y * ray.camera_x;
		d.map_x = (int)(ray.pos_x);
		d.map_y = (int)(ray.pos_y);
		ray.delta_dist_x = sqrt(1 + (ray.dir_y * ray.dir_y) /
			(ray.dir_x * ray.dir_x));
		ray.delta_dist_y = sqrt(1 + (ray.dir_x * ray.dir_x) /
			(ray.dir_y * ray.dir_y));
		d.hit = 0;
		define_step(&ray, &d);
		perform_dda(&ray, p, &d);
		pixel_fill(&ray, p, &d);
		draw_line(p, d.draw_start, x, &d);
		x++;
	}
}
