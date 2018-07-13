/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_wolf3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 13:19:12 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/29 11:18:39 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			put_pixels(t_param *p, int x, int y, unsigned int color)
{
	char	*pos;

	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		pos = p->data + p->size_line * y + x * (p->bpp / 8);
		*pos = color;
		*(pos + 1) = color >> 8;
		*(pos + 2) = color >> 16;
	}
}
