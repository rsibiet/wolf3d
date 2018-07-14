/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_wolf3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 11:36:13 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 13:50:51 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			put_pixels(t_param *p, int x, int y)
{
	char	*pos;

	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0 && p->furious == 1)
	{
		pos = p->data + p->size_line * y + x * (p->bpp / 8);
		*pos = p->color;
		*(pos + 1) = (p->color >> 8);
		*(pos + 2) = (p->color >> 16);
		*(pos + 3) = p->drug_mode;
	}
	else if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		pos = p->data + p->size_line * y + x * (p->bpp / 8);
		*pos = 0;
		*(pos + 1) = 0;
		if (p->line_height < 16)
			*(pos + 2) = 32;
		else
			*(pos + 2) = 255 - 3568 / p->line_height;
	}
}

void				draw_line(t_param *p, int y_start, int x)
{
	y_start -= 1;
	while (++y_start < p->draw_end)
		put_pixels(p, x, y_start);
}

void				ft_error(char *c, t_param *p)
{
	ft_putstr_fd("wolf3d : ", 2);
	ft_putendl_fd(c, 2);
	ft_strdel(&p->lvl_nb);
	ft_strdel_del(&p->lvl_map);
	ft_strdel(&c);
	if (p->img[0] != NULL)
		mlx_destroy_image(p->mlx, p->img[0]);
	if (p->img[1] != NULL)
		mlx_destroy_image(p->mlx, p->img[1]);
	if (p->win != NULL)
		mlx_destroy_window(p->mlx, p->win);
	p->mlx = NULL;
	p->img[0] = NULL;
	p->img[1] = NULL;
	exit(EXIT_FAILURE);
}

void				error_wolf3d(char *c, t_param *p)
{
	ft_putstr_fd("wolf3d : ", 2);
	ft_putstr_fd(c, 2);
	perror(" ");
	ft_strdel(&p->lvl_nb);
	if (p->lvl_map != NULL)
		ft_strdel_del(&p->lvl_map);
	exit(EXIT_FAILURE);
}

char				**loading_lvl(int nb_line, int fd, char *lvl_name,
						t_param *p)
{
	char	**lvl;
	char	*line;

	if ((fd = open(lvl_name, O_RDONLY)) == -1)
		error_wolf3d(lvl_name, p);
	while (get_next_line(fd, &line) > 0)
	{
		nb_line++;
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		error_wolf3d(lvl_name, p);
	if ((lvl = (char **)malloc(sizeof(char *) * (nb_line + 1))) == NULL)
		error_wolf3d("lvl", p);
	nb_line = 0;
	if ((fd = open(lvl_name, O_RDONLY)) == -1)
		error_wolf3d(lvl_name, p);
	while (get_next_line(fd, &lvl[nb_line]) > 0)
		nb_line++;
	if (close(fd) == -1)
		error_wolf3d(lvl_name, p);
	lvl[nb_line] = NULL;
	return (lvl);
}
