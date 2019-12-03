#include "lem-in.h"

int ifcomments(char *str)
{
	if (str[0] == '#' && (str[1] != '#' || !str[1]))
	{
		free(str);
		return (1);
	}
	return (0);
}

void	check_name_coord(char **room)
{
	unsigned i;

	i = 0;
	while (room[i])
		i++;
	i > 3 ? ft_error_str("more than two coordinates") : 0;
	i == 2 ? ft_error_str("only one coordinate") : 0;
	i == 1 ? ft_error_str("only room") : 0;
}

void	ft_start(t_all *all, int fd, char *str)
{
	char **room;

	room = NULL;
	all->first_room ? ft_error_str("double start") : 0;
	while (get_next_line(fd, &str) && ifcomments(str))
	{
	}
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("don't have a room");
	free(str);
	all->first_room = ft_create(room);
	all->number_of_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew_ptr(all->first_room));
}

void	ft_end(t_all *all, int fd, char *str)
{
	char **room;

	room = NULL;
	all->last_room ? ft_error_str("double finish") : 0;
	while (get_next_line(fd, &str) && ifcomments(str))
	{
	}
	ft_printf("%s\n", str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("don't have a room");
	free(str);
	all->last_room = ft_create(room);
	all->number_of_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew_ptr(all->last_room));
}

int		start_end(t_all *map, int fd, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		free(str);
		str = NULL;
		ft_start(map, fd, str);
		return (1);
	}
	else if (!ft_strcmp(str, "##end"))
	{
		free(str);
		str = NULL;
		ft_end(map, fd, str);
		return (1);
	}
	return (0);
}

void		room_coord(t_all *all, char *str)
{
	char	**room;
	t_rooms	*temp;

	room = NULL;
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("NO ROOM");
	free(str);
	temp = ft_create(room);
	all->number_of_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew_ptr(temp));
}

t_list	*next(t_list *tmp)
{
	t_list *next;

	next = NULL;
	if (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	return (next);

}

void 	double_name(t_all *all)
{
	unsigned i;
	unsigned  j;


	i = 0;
	j = 1;
	while(i < all->number_of_rooms)
	{
		while (j < all->number_of_rooms)
		{
			if (ft_strcmp(all->arr_rooms[i]->name, all->arr_rooms[j]->name))
				j++;
			else
				ft_error_str("double name");
		}
		i++;
		j = i + 1;
	}
}

void				ft_sort(t_all *all)
{

}

void	struct_to_array(t_all *all)
{
	t_list		*tmp;
	unsigned	i;

	i = 0;
	tmp = all->list_of_rooms;
	if (!(all->arr_rooms = ft_memalloc(sizeof(t_rooms *) * (all->number_of_rooms)))) //+1 ????
		exit(1);
	while (tmp)
	{
		all->arr_rooms[i++] = tmp->content;
		tmp = next(tmp);
	}
	all->list_of_rooms = NULL; ///список с комнатами уже не нужен, есть массив, так-что обнуляем и не храним
	double_name(all);
	!all->first_room || !all->last_room ? ft_error_str("no start/finish") : 0;
	ft_sort(all);
	i = 0;
//	while (i < all->number_of_rooms)
//	{
//		all->arr_rooms[i]->n = i;
//		++i;
//	}
}

void				links_in_array(t_all *all, char *str)
{

}

void	all_rooms(t_all *all, int fd)
{
	char	*str;
	unsigned char	tmp;

	tmp = 0;
	str = NULL;
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		if (ifcomments(str)) ///ищем комментарий и пропускаем его
			continue;
		else if (start_end(all, fd, str) && !tmp) ///ищем ##start && ##end
			continue;
		else if (ft_strchr(str, ' ') && !tmp) ///записываем комнату и ее координаты
			room_coord(all, str);
		else if (ft_strchr(str, '-') && !tmp)
		{
			struct_to_array(all);
			tmp = 1;
			links_in_array(all, str);
		}
		else if(ft_strchr(str, '-'))
			links_in_array(all, str);
	}
}
