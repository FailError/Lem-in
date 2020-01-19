/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comments_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:51:47 by bgilwood          #+#    #+#             */
/*   Updated: 2020/01/18 22:18:11 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		comments_or_commands(char *str, int c)
{
	if (str[0] && str[0] == '#' && (!str[1] || str[1] != '#') && !c)
	{
		free(str);
		return (1);
	}
	else if (str[0] && str[0] == '#' && (!str[1] || str[1] != '#') && c)
	{
		ft_putstr(str);
		free(str);
		return (1);
	}
	else if (str[0] == '#' && str[1] == '#' &&
				ft_strcmp(str, "##start") && ft_strcmp(str, "##end"))
	{
		ft_putstr(str);
		free(str);
		return (1);
	}
	return (0);
}

void	ft_start(t_all *all, int fd)
{
	char	**room;
	char	*str;

	all->first_room ? error("double start") : 0;
	get_next_line(fd, &str);
	while (comments_or_commands(str, 1))
		get_next_line(fd, &str);
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("no room!");
	free(str);
	all->first_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->first_room));
	all->n_rooms++;
	all->first_room->lvl = 0;
}

void	ft_end(t_all *all, int fd)
{
	char	**room;
	char	*str;

	all->last_room ? error("double finish") : 0;
	get_next_line(fd, &str);
	while (comments_or_commands(str, 1))
		get_next_line(fd, &str);
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("no room!");
	free(str);
	all->last_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->last_room));
	all->n_rooms++;
	all->last_room->lvl = INT_MAX;
}

int		start_end(t_all *all, int fd, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		free(str);
		ft_start(all, fd);
		return (1);
	}
	else if (!ft_strcmp(str, "##end"))
	{
		free(str);
		ft_end(all, fd);
		return (1);
	}
	return (0);
}
