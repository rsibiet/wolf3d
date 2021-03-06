/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 17:28:21 by rsibiet           #+#    #+#             */
/*   Updated: 2016/03/07 13:44:39 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strdel_del(char ***c)
{
	int		i;

	i = 0;
	while ((*c)[i] != NULL)
	{
		ft_strdel(*c + i);
		i++;
	}
	free(*c);
	*c = NULL;
}
