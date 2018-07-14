/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:58:41 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 12:50:37 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_winner(t_param *p, int x, int j)
{
	char		*c;

	c = ft_itoa(p->timer * 50);
	p->game_over = 1;
	ft_bzero(p->data, p->size_line * HEIGHT);
	mlx_put_image_to_window(p->mlx, p->win, p->img[1], 0, HEIGHT - 100);
	mlx_put_image_to_window(p->mlx, p->win, p->img[0], 0, 0);
	j = 380;
	mlx_string_put(p->mlx, p->win, x = 760, j, GREEN, "YOU WIN !");
	mlx_string_put(p->mlx, p->win, x -= 45, j += 25, 0x002277FF,
			"Congratulations !!!");
	mlx_string_put(p->mlx, p->win, x += 25, j += 25, 0x00FFFF00, "Score :");
	mlx_string_put(p->mlx, p->win, x += 80, j, 0x00FFFF00, c);
	mlx_string_put(p->mlx, p->win, x -= 70, j += 25, 0x00CCCCCC,
			"Quit: [esc]");
}

static void		timer_2(t_param *p, int x, int j)
{
	char	*c;

	c = NULL;
	if (p->timer != 0)
	{
		mlx_string_put(p->mlx, p->win, x = 85, j += 40, 0x00BBBBBB,
			c = ft_itoa(p->timer));
		ft_strdel(&c);
	}
	else
	{
		p->game_over = 1;
		ft_bzero(p->data, p->size_line * HEIGHT);
		mlx_put_image_to_window(p->mlx, p->win, p->img[1], 0, HEIGHT - 100);
		mlx_put_image_to_window(p->mlx, p->win, p->img[0], 0, 0);
		j = 380;
		mlx_string_put(p->mlx, p->win, x = 720, j, RED,
			"GAME OVER (TIME OUT)");
		mlx_string_put(p->mlx, p->win, x += 40, j += 25, 0x00CCCCCC,
			"Try again...");
		mlx_string_put(p->mlx, p->win, x += 5, j += 25, 0x00CCCCCC,
			"Quit: [esc]");
	}
}

static void		timer(t_param *p, int x, int j)
{
	time_t	*t;

	t = NULL;
	if (p->memo_t != time(t) && p->game_over == 0)
	{
		p->memo_t = time(t);
		(p->timer)--;
		if (p->furious == -1)
			(p->time_furious)--;
		else if (p->time_furious < 5)
		{
			p->tp_furious *= -1;
			if (p->tp_furious == 1)
				(p->time_furious)++;
		}
	}
	if (p->time_furious == 0)
	{
		p->mv_speed = 0.3;
		p->furious = 1;
	}
	timer_2(p, x, j);
}

static void		user_interface_2(t_param *p, int x, int j)
{
	if (p->drug_mode == 253)
		mlx_string_put(p->mlx, p->win, x -= 150, j += 20, RED,
				"Current mode : DRUG & ALCOHOL");
	if (p->furious == 1)
		mlx_string_put(p->mlx, p->win, x, j += 20, 0x0033FF66, "Stat : relax");
	else
		mlx_string_put(p->mlx, p->win, x, j += 20, 0x00CC0000,
				"Stat : furious");
	mlx_string_put(p->mlx, p->win, x, j += 20, 0x00BBBBBB,
			"Time :");
	mlx_string_put(p->mlx, p->win, x += 390, j = HEIGHT - 98, 0x0033C1B1,
			"Controls");
	mlx_string_put(p->mlx, p->win, x -= 70, j += 25, 0x0033C1B1,
			"Move : cross");
	mlx_string_put(p->mlx, p->win, x, j += 22, 0x0033C1B1,
			"Furious stat : space");
	mlx_string_put(p->mlx, p->win, x, j += 22, 0x0033C1B1,
			"Drug mode : 0");
	mlx_string_put(p->mlx, p->win, x += 240, j -= 45, 0x0099FF99,
			"Mission : Find the pink zone to go to next level.");
	mlx_string_put(p->mlx, p->win, x, j += 25, 0x0099FF99,
			"Finish the 3 levels before time out.");
	mlx_string_put(p->mlx, p->win, x = 1430, j += 20, 0x00CCCCCC,
			"Quit game: [esc]");
}

void			user_interface(t_param *p, int x, int j)
{
	if (p->game_over == 0)
	{
		mlx_string_put(p->mlx, p->win, x, j = HEIGHT - 90,
				0x006669FF, "Level        :");
		mlx_string_put(p->mlx, p->win, x += 150, j, 0x006669FF, p->lvl_nb);
		if (p->drug_mode == 0)
			mlx_string_put(p->mlx, p->win, x -= 150, j += 20, YELLOW,
					"Current mode : NORMAL");
		else if (p->drug_mode == 245)
			mlx_string_put(p->mlx, p->win, x -= 150, j += 20, 16711833,
					"Current mode : DRUG");
		user_interface_2(p, x, j);
		j = 852;
		if (p->time_furious >= 1)
			mlx_string_put(p->mlx, p->win, x = 165, j, RED, "-");
		if (p->time_furious >= 2)
			mlx_string_put(p->mlx, p->win, x = 180, j, RED, "-");
		if (p->time_furious >= 3)
			mlx_string_put(p->mlx, p->win, x = 195, j, RED, "-");
		if (p->time_furious >= 4)
			mlx_string_put(p->mlx, p->win, x = 210, j, RED, "-");
		if (p->time_furious == 5)
			mlx_string_put(p->mlx, p->win, x = 225, j, RED, "-");
	}
	timer(p, 8, 830);
}
