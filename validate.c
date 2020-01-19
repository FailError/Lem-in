/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:36:42 by bgilwood          #+#    #+#             */
/*   Updated: 2020/01/18 22:28:34 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				double_name(t_all *all)
{
	unsigned		i;
	unsigned		j;

	i = 0;
	while (i < all->n_rooms)
	{
		j = i + 1;
		while (j < all->n_rooms)
		{
			if (all->ar_room[i]->x == all->ar_room[j]->x &&
			all->ar_room[i]->y == all->ar_room[j]->y)
			{
				ft_printf("\x1B[31mdouble coord \033[0m%s[%d;%d] && %s[%d;%d]",
				all->ar_room[i]->name, all->ar_room[i]->x, all->ar_room[i]->y,
				all->ar_room[j]->name, all->ar_room[j]->x, all->ar_room[j]->y);
				exit(0);
			}
			if (!ft_strcmp(all->ar_room[i]->name, all->ar_room[j]->name))
				error("double name");
			j++;
		}
		i++;
	}
}

void				check_name_coord(char **room)
{
	unsigned		i;

	i = 0;
	while (room[i])
		i++;
	i > 3 ? error("more than two coordinates") : 0;
	i == 2 ? error("only one coordinate or wrong links") : 0;
	i == 1 ? error("only room") : 0;
	i == 0 ? error("no room") : 0;
}

void				check_links(char **room)
{
	unsigned		i;

	i = 0;
	while (room[i])
		i++;
	i != 2 ? error("error links") : 0;
}

void				doubleminus(const char *str)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	if (j > 1)
		error("double minus");
}
