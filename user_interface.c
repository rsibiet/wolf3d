/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:58:41 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/27 13:06:47 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		user_interface_2(t_param *p, int i, int j)
{
	mlx_string_put(p->mlx, p->win, i -= 90, j += 20, 0x0033C1B1,
			"Zoom : mouse");
	mlx_string_put(p->mlx, p->win, i, j += 20, 0x0033C1B1,
			"Iteration nb : '+' & '-'");
	mlx_string_put(p->mlx, p->win, i, j += 20, 0x0033C1B1,
			"Move : 2, 4, 6, 8");
	mlx_string_put(p->mlx, p->win, i, j += 20, 0x0033C1B1,
			"change color : 0");
	mlx_string_put(p->mlx, p->win, i, j += 20, 0x0033C1B1,
			"freeze screen : 1");
}

void			user_interface(t_param *p, int x, int i, int j)
{
	x = WIDTH;
	i = x - 280;
	j = 145;
	while (i++ < (x - 11))
		mlx_pixel_put(p->mlx, p->win, i, j, 0x0033C1B1);
	while (j-- > 11)
		mlx_pixel_put(p->mlx, p->win, i, j, 0x0033C1B1);
	while (i-- > (x - 280))
		mlx_pixel_put(p->mlx, p->win, i, j, 0x0033C1B1);
	while (j++ < 145)
		mlx_pixel_put(p->mlx, p->win, i, j, 0x0033C1B1);
	mlx_string_put(p->mlx, p->win, i += 10, j = 15, 0x0033C1B1, "level : ");
	i += 90;
	user_interface_2(p, i, j);
}
