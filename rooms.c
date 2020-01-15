/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:02:18 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/15 20:56:41 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int				comments(char *str, int c)
{
	if (str[0] && str[0] == '#' && (!str[1] || str[1] != '#') && !c)
	{
		free(str);
		str = NULL;
		return (1);
	}
	else if (str[0] && str[0] == '#' && (!str[1] || str[1] != '#') && c)
	{
		ft_putstr(str);
		free(str);
		return (1);
	}
	return (0);
}

void			check_name_coord(char **room)
{
	unsigned	i;

	i = 0;
	while (room[i])
		i++;
	i > 3 ? error("more than two coordinates") : 0;
	i == 2 ? error("only one coordinate or wrong links") : 0;
	i == 1 ? error("only room") : 0;
	i == 0 ? error("NO ROOM") : 0;
//	i != 3 ? ft_error_str("\x1B[31mError\033[0m") : 0;
}

void		ft_start(t_all *all, int fd)
{
	char	**room;
 	char	*str;
	
	all->first_room ? error("double start") : 0;
	get_next_line(fd, &str);
	while (comments(str, 1))
	{
		get_next_line(fd, &str);
	}
	ft_putstr(str); // сега если комментарий, была...
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	all->first_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->first_room));
	all->number_of_all_rooms++;
	all->first_room->lvl = 0;
}

void		ft_end(t_all *all, int fd)
{
	char	**room;
	char	*str;

	all->last_room ? error("double finish") : 0;
	get_next_line(fd, &str);
	while (comments(str, 1))
	{
//		ft_putstr(str);
		get_next_line(fd, &str);
	}
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	all->last_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->last_room));
	all->number_of_all_rooms++;
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
	else if(str[0] == '#' && str[1] == '#')
		return(1);
	return (0);
}

void		room_coord(t_all *all, char *str)
{
	char	**room;
	t_rooms	*tmp;

	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : error("NO ROOM");
	free(str);
	tmp = ft_create(room);
	all->number_of_all_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(tmp));
}

t_list		*next(t_list *tmp)
{
	t_list	*next;

	next = NULL;
	if (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	return (next);

}

void			double_name(t_all *all)
{
	unsigned	i;
	unsigned 	j;

	i = 0;
	while (i < all->number_of_all_rooms)
	{
		j = i + 1;
		while (j < all->number_of_all_rooms)
		{
			if(all->arr_rooms[i]->x == all->arr_rooms[j]->x && all->arr_rooms[i]->y == all->arr_rooms[j]->y)
			{
				ft_printf("\x1B[31mdouble coord \033[0m%s[%d;%d] && %s[%d;%d]", all->arr_rooms[i]->name, all->arr_rooms[i]->x, all->arr_rooms[i]->y,   all->arr_rooms[j]->name, all->arr_rooms[j]->x, all->arr_rooms[j]->y);
				exit(0);
			}
			if (ft_strcmp(all->arr_rooms[i]->name, all->arr_rooms[j]->name))
				j++;
			else
				error("double name");
		}
		i++;
	}
}

void	qs_swap(t_rooms **arr_rooms, t_rooms *tmp, int *left, int *right)
{
	tmp = arr_rooms[*left];
	arr_rooms[*left] = arr_rooms[*right];
	arr_rooms[*right] = tmp;
	*left += 1;
	*right -=1;
}

void		quick_sort(t_rooms **arr_rooms, int first, int last)
{
	t_rooms	*tmp;
	int		left;
	int		right;
	char	*middle;

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

void			struct_to_array(t_all *all)
{
	unsigned	i;

	!all->first_room || !all->last_room ? error("no start/finish") : 0;
	all->arr_rooms = ft_memalloc(sizeof(t_rooms *) * all->number_of_all_rooms); //+1 ????

	i = 0;
	while (all->list_of_rooms)
	{
		all->arr_rooms[i] = all->list_of_rooms->content;
		all->list_of_rooms = next(all->list_of_rooms);
		i++;
	}
	all->list_of_rooms = NULL; ///список с комнатами уже не нужен, есть массив, так-что обнуляем и не храним, фришить кто будет??
	double_name(all); //проверка на дубликат имен комнат
	quick_sort(all->arr_rooms, 0, (int)all->number_of_all_rooms - 1); ///сортируем комнаты в массиве arr_rooms по алфавиту
}

t_rooms		*binary_search(char *current, unsigned all_rooms, t_rooms **rooms)
{
	int		low;
	int		high;
	int		mid;
	char	*guess;

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
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
}

int 				check_room_on_list(t_list *links, t_rooms *room)
{
	t_list	*current_list;
	t_rooms	*current_room;
	int 	success;

	current_list = links;
	success = 0;
	while (current_list != NULL)
	{
		current_room = current_list->content;
		if(ft_strcmp(current_room->name, room->name) == 0)
		{
			success = 1;
			return (success);
		}
		current_list = current_list->next;
	}
	return (success);
}

void				doubleminus(const char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	while(str[i])
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
	char	**tmp;
	t_rooms	*first;
	t_rooms	*second;

	//doubleminus(str);
	tmp = ft_strsplit(str, '-');
	//check_name_coord2(tmp);
	doubleminus(str);
	if (!(first = binary_search(tmp[0], all->number_of_all_rooms, all->arr_rooms)))
		error("Error, room not found");
	if (!(second = binary_search(tmp[1], all->number_of_all_rooms, all->arr_rooms)))
		error("Error, room not found");
	check_room_on_list(first->links, second) ? 0 : ft_lstadd(&first->links, ft_lstnew2(second));
	check_room_on_list(second->links, first) ? 0 : ft_lstadd(&second->links, ft_lstnew2(first));
	free(str);
	free_str_double_star(tmp);
}

void	all_rooms(t_all *all, int fd)
{
	char 			*str;
	unsigned char	links_started;

	links_started = 0;
	str = NULL;
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		if (comments(str, 0)) ///ищем комментарий и пропускаем его
			;//do nothing
		else if (start_end(all, fd, str) && !links_started) ///ищем ##start && ##end
			continue;
		else if (ft_strchr(str, ' ') && !links_started) ///записываем комнату и ее координаты
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
	!all->arr_rooms ? error("links not found") : 0;
}
