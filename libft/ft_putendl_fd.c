/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:50:08 by rsibiet           #+#    #+#             */
/*   Updated: 2015/11/25 16:29:32 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s);
	j = 0;
	while (j < i)
	{
		ft_putchar_fd(s[j], fd);
		j++;
	}
	ft_putchar_fd('\n', fd);
}
