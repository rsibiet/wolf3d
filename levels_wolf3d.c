/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_wolf3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 11:36:13 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/27 14:55:07 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			error_wolf3d(char *c)
{
	ft_putstr_fd("wolf3d : ", 2);
	ft_putstr_fd(c, 2);
	perror(" ");
	exit(EXIT_FAILURE);
}

char			**loading_lvl(int nb_line, int fd, char *lvl_name)
{
	char	**lvl;
	char	*line;
	
	if ((fd = open(lvl_name, O_RDONLY)) == -1)
		error_wolf3d(lvl_name);
	while (get_next_line(fd, &line) > 0)
	{
		nb_line++;
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		error_wolf3d(lvl_name);
	if ((lvl = (char **)malloc(sizeof(char *) * (nb_line + 1))) == NULL)
		error_wolf3d("lvl");
	nb_line = 0;
	if ((fd = open(lvl_name, O_RDONLY)) == -1)
		error_wolf3d(lvl_name);
	while (get_next_line(fd, &lvl[nb_line]) > 0)
		nb_line++;
	if (close(fd) == -1)
		error_wolf3d(lvl_name);
	lvl[nb_line] = NULL;
	return (lvl);
}
