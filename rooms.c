/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:50:26 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 22:16:42 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				room_coord(t_all *all, char *str)
{
	char			**room;
	t_rooms			*tmp;

	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	tmp = ft_create(room);
	all->n_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(tmp));
}

t_list				*next(t_list *tmp)
{
	t_list			*next;

	next = NULL;
	if (tmp)
	{
		next = tmp->next;
		free(tmp);
	}
	return (next);
}

int					check_double_room_in_list(t_list *links, t_rooms *room)
{
	t_list			*current_list;
	t_rooms			*current_room;

	current_list = links;
	while (current_list != NULL)
	{
		current_room = current_list->content;
		if (!ft_strcmp(current_room->name, room->name))
			return (1);
		current_list = current_list->next;
	}
	return (0);
}

void				links_add(t_all *all, char *str)
{
	char			**tmp;
	t_rooms			*first;
	t_rooms			*second;

	tmp = ft_strsplit(str, '-');
	doubleminus(str);
	check_links(tmp);
	if (!(first = binary_search(tmp[0], all->n_rooms, all->ar_room)))
	{
		free(str);
		error("Error, room not found");
	}
	if (!(second = binary_search(tmp[1], all->n_rooms, all->ar_room)))
	{
		free(str);
		error("Error, room not found");
	}
	if (!(check_double_room_in_list(first->links, second)))
		ft_lstadd(&first->links, ft_lstnew2(second));
	if (!(check_double_room_in_list(second->links, first)))
		ft_lstadd(&second->links, ft_lstnew2(first));
	free(str);
	free_str_double_star(tmp);
}

void				all_rooms(t_all *all, int fd)
{
	char			*str;
	unsigned char	links_started;

	links_started = 0;
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		if (comments_or_commands(str, 0))
			;
		else if (start_end(all, fd, str) && !links_started)
			continue;
		else if (ft_strchr(str, ' ') && !links_started)
			room_coord(all, str);
		else if (ft_strchr(str, '-') && !links_started)
		{
			struct_to_array(all);
			links_started = 1;
			links_add(all, str);
		}
		else if (ft_strchr(str, '-'))
			links_add(all, str);
		else
			error("Error");
	}
	!all->ar_room ? error("links not found") : 0;
}
