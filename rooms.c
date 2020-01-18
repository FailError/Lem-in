/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:50:26 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 15:38:47 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					comments_or_commands(char *str, int c)
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

void				check_name_coord(char **room)
{
	unsigned		i;

	i = 0;
	while (room[i])
		i++;
	i > 3 ? error("more than two coordinates") : 0;
	i == 2 ? error("only one coordinate or wrong links") : 0;
	i == 1 ? error("only room") : 0;
	i == 0 ? error("NO ROOM") : 0;
}

void				ft_start(t_all *all, int fd)
{
	char			**room;
	char			*str;

	all->first_room ? error("double start") : 0;
	get_next_line(fd, &str);
	while (comments_or_commands(str, 1))
		get_next_line(fd, &str);
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	all->first_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->first_room));
	all->num_all_rooms++;
	all->first_room->lvl = 0;
}

void				ft_end(t_all *all, int fd)
{
	char			**room;
	char			*str;

	all->last_room ? error("double finish") : 0;
	get_next_line(fd, &str);
	while (comments_or_commands(str, 1))
		get_next_line(fd, &str);
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	all->last_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->last_room));
	all->num_all_rooms++;
	all->last_room->lvl = INT_MAX;
}

int					start_end(t_all *all, int fd, char *str)
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

void				room_coord(t_all *all, char *str)
{
	char			**room;
	t_rooms			*tmp;

	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	tmp = ft_create(room);
	all->num_all_rooms++;
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

void				double_name(t_all *all)
{
	unsigned		i;
	unsigned		j;

	i = 0;
	while (i < all->num_all_rooms)
	{
		j = i + 1;
		while (j < all->num_all_rooms)
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

void				qs_swap(t_rooms **arr_rooms, t_rooms *tmp,
					int *left, int *right)
{
	tmp = arr_rooms[*left];
	arr_rooms[*left] = arr_rooms[*right];
	arr_rooms[*right] = tmp;
	*left += 1;
	*right -= 1;
}

void				quick_sort(t_rooms **arr_rooms, int first, int last)
{
	t_rooms			*tmp;
	int				left;
	int				right;
	char			*middle;

	tmp = NULL;
	if (first < last)
	{
		left = first;
		right = last;
		middle = arr_rooms[(left + right) / 2]->name;
		while (left <= right)
		{
			while ((ft_strcmp(arr_rooms[left]->name, middle) < 0))
				left++;
			while ((ft_strcmp(arr_rooms[right]->name, middle) > 0))
				right--;
			if (left <= right)
				qs_swap(arr_rooms, tmp, &left, &right);
		}
		quick_sort(arr_rooms, first, right);
		quick_sort(arr_rooms, left, last);
	}
}

void				struct_to_array(t_all *all)
{
	unsigned		i;

	!all->first_room || !all->last_room ? error("no start/finish") : 0;
	all->ar_room = ft_memalloc(sizeof(t_rooms *) * all->num_all_rooms);
	i = 0;
	while (all->list_of_rooms)
	{
		all->ar_room[i] = all->list_of_rooms->content;
		all->list_of_rooms = next(all->list_of_rooms);
		i++;
	}
	all->list_of_rooms = NULL;
	double_name(all);
	quick_sort(all->ar_room, 0, (int)all->num_all_rooms - 1);
}

t_rooms				*binary_search(char *current, unsigned all_rooms,
					t_rooms **rooms)
{
	int				low;
	int				high;
	int				mid;
	char			*guess;

	low = 0;
	high = (int)all_rooms - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		guess = rooms[mid]->name;
		if (!ft_strcmp(guess, current))
			return (rooms[mid]);
		if (ft_strcmp(guess, current) > 0)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return (NULL);
}

void				free_str_double_star(char **str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
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

void				check_name_coord2(char **room)
{
	unsigned		i;

	i = 0;
	while (room[i])
		i++;
	i != 2 ? error("Error links") : 0;
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

void				links_add(t_all *all, char *str)
{
	char			**tmp;
	t_rooms			*first;
	t_rooms			*second;

	tmp = ft_strsplit(str, '-');
	doubleminus(str);
	check_name_coord2(tmp);
	if (!(first = binary_search(tmp[0], all->num_all_rooms, all->ar_room)))
	{
		free(str);
		error("Error, room not found");
	}
	if (!(second = binary_search(tmp[1], all->num_all_rooms, all->ar_room)))
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
