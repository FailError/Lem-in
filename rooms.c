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
	i == 2 ? ft_error_str("only one coordinate or wrong links") : 0;
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
	room ? check_name_coord(room) : ft_error_str("NO ROOM");
	free(str);
	all->first_room = ft_create(room);
	all->number_of_all_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->first_room));
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
	room ? check_name_coord(room) : ft_error_str("NO ROOM");
	free(str);
	all->last_room = ft_create(room);
	all->number_of_all_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->last_room));
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
	all->number_of_all_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(temp));
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
	while (i < all->number_of_all_rooms)
	{
		while (j < all->number_of_all_rooms)
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
void	qs22(t_all *all, char *tmp, int *left, int *right)
{
	tmp = all->arr_rooms[*left]->name;
	all->arr_rooms[*left]->name = all->arr_rooms[*right]->name;
	all->arr_rooms[*right]->name = tmp;
	*left += 1;
	*right -=1;
}

void	qs2(t_all *all, int first, int last)
{
	char *tmp;
	int left;
	int right;
	char *middle;

	tmp = NULL;
	if (first < last)
	{
		left = first;
		right = last;
		middle = all->arr_rooms[(left + right) / 2]->name;
		while (left <= right)
		{
			while ((ft_strcmp(all->arr_rooms[left]->name, middle) < 0))
				left++;
			while ((ft_strcmp(all->arr_rooms[right]->name, middle) > 0))
				right--;
			if (left <= right)
				qs22(all, tmp, &left, &right);
		}
		qs2(all, first, right);
		qs2(all, left, last);
	}
}

void	struct_to_array(t_all *all)
{
	t_list		*tmp;
	unsigned	i;

	i = 0;
	tmp = all->list_of_rooms;
	!all->first_room || !all->last_room ? ft_error_str("no start/finish") : 0;
	if (!(all->arr_rooms = ft_memalloc(sizeof(t_rooms *) * (all->number_of_all_rooms)))) //+1 ????
		exit(1);
	while (tmp)
	{
		all->arr_rooms[i++] = tmp->content;
		tmp = next(tmp);
	}
	all->list_of_rooms = NULL; ///список с комнатами уже не нужен, есть массив, так-что обнуляем и не храним
	double_name(all); //проверка на дубликат имен комнат
	qs2(all, 0, all->number_of_all_rooms - 1); ///сортируем комнаты в массиве arr_rooms по алфавиту
	i = 0;
	while (i < all->number_of_all_rooms) //присваиваем комнатам их порядковый номер
	{
		all->arr_rooms[i]->num = i;
		i++;
	}
}

void				check_name_coord2(char **room)
{
	unsigned i;

	i = 0;
	while (room[i])
		i++;
	i != 2 ? ft_error_str("Error links") : 0;
}

t_rooms *binary_search(char *current, unsigned all_rooms, t_rooms **rooms)
{
	unsigned low;
	unsigned high;
	unsigned mid;
	char *guess;

	low = 0;
	high = all_rooms - 1;

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
	//ft_error_str("Error links");
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

void				links_in_array(t_all *all, char *str)
{
	char **tmp;
	t_rooms *first;
	t_rooms *second;

	tmp = NULL;
	tmp = ft_strsplit(str, '-');
	check_name_coord2(tmp);
	if(!(first = binary_search(tmp[0], all->number_of_all_rooms, all->arr_rooms)))
		ft_error_str("Error links");
	if(!(second = binary_search(tmp[1], all->number_of_all_rooms, all->arr_rooms)))
		ft_error_str("Error links");
	ft_lstadd(&first->links, ft_lstnew2(second));
	ft_lstadd(&second->links, ft_lstnew2(first));
	free(str);
	free_str_double_star(tmp);
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
		else
			ft_error_str("Error");
	}
}
