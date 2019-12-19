#include "lem-in.h"

int ifcomments(char *str)
{
	if (str[0] && str[0] == '#' && (!str[1] || str[1] != '#'))
	{
		free(str);
		str = NULL;
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
	i > 3 ? ft_error_str("\x1B[31mmore than two coordinates\033[0m") : 0;
	i == 2 ? ft_error_str("\x1B[31monly one coordinate or wrong links\033[0m") : 0;
	i == 1 ? ft_error_str("\x1B[31monly room\033[0m") : 0;
	i == 0 ? ft_error_str("\x1B[31mNO ROOM\033[0m") : 0;
//	i != 3 ? ft_error_str("\x1B[31mError\033[0m") : 0;
}

void	ft_start(t_all *all, int fd, char *str)
{
	char **room;

	all->first_room ? ft_error_str("\x1B[31mdouble start\033[0m") : 0;
	get_next_line(fd, &str);
	while(ifcomments(str))
	{
		ft_putstr(str);
		get_next_line(fd, &str);
	}
	ft_putstr(str); // сега если комментарий, была...
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("\x1B[31mNO ROOM\033[0m");
	free(str);
	all->first_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->first_room));
	all->number_of_all_rooms++;
}

void	ft_end(t_all *all, int fd, char *str)
{
	char **room;

	all->last_room ? ft_error_str("\x1B[31mdouble finish\033[0m") : 0;
	get_next_line(fd, &str);
	while(ifcomments(str))
		get_next_line(fd, &str);
	ft_putstr(str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("\x1B[31mNO ROOM\033[0m");
	free(str);
	all->last_room = ft_create(room);
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(all->last_room));
	all->number_of_all_rooms++;
}

int		start_end(t_all *all, int fd, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		free(str);
		str = NULL;
		ft_start(all, fd, str);
		return (1);
	}
	else if (!ft_strcmp(str, "##end"))
	{
		free(str);
		str = NULL;
		ft_end(all, fd, str);
		return (1);
	}
	return (0);
}

void		room_coord(t_all *all, char *str)
{
	char	**room;
	t_rooms	*tmp;

	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("\x1B[31mNO ROOM\033[0m");
	free(str);
	tmp = ft_create(room);
	all->number_of_all_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew2(tmp));
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
	while (i < all->number_of_all_rooms)
	{
		j = i + 1;
		while (j < all->number_of_all_rooms)
		{
			if (ft_strcmp(all->arr_rooms[i]->name, all->arr_rooms[j]->name))
				j++;
			else
				ft_error_str("\x1B[31mdouble name\033[0m");
		}
		i++;
	}
}
void	qs_swap(t_all *all, t_rooms *tmp, int *left, int *right)
{
	tmp = all->arr_rooms[*left];
	all->arr_rooms[*left] = all->arr_rooms[*right];
	all->arr_rooms[*right] = tmp;
	*left += 1;
	*right -=1;
}

void	quick_sort(t_all *all, int first, int last)
{
	t_rooms *tmp;
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
				qs_swap(all, tmp, &left, &right);
		}
		quick_sort(all, first, right);
		quick_sort(all, left, last);
	}
}

void	struct_to_array(t_all *all)
{
	t_list		*tmp;
	unsigned	i;

	tmp = all->list_of_rooms;
	!all->first_room || !all->last_room ? ft_error_str("\x1B[31mno start/finish\033[0m") : 0;
	if (!(all->arr_rooms = ft_memalloc(sizeof(t_rooms *) * all->number_of_all_rooms))) //+1 ????
		exit(1);
	i = 0;
	while (all->list_of_rooms)
	{
		all->arr_rooms[i] = all->list_of_rooms->content;
		all->list_of_rooms = next(all->list_of_rooms);
		i++;
	}
	all->list_of_rooms = NULL; ///список с комнатами уже не нужен, есть массив, так-что обнуляем и не храним, фришить кто будет??
	double_name(all); //проверка на дубликат имен комнат
	quick_sort(all, 0, all->number_of_all_rooms - 1); ///сортируем комнаты в массиве arr_rooms по алфавиту
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
	i != 2 ? ft_error_str("\x1B[31mError links\033[0m") : 0;
}

t_rooms *binary_search(char *current, unsigned all_rooms, t_rooms **rooms)
{
	int low;
	int high;
	int mid;
	char *guess;

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

void				links_in_array(t_all *all, char *str)
{
	char **tmp;
	t_rooms *first;
	t_rooms *second;

	tmp = ft_strsplit(str, '-');
	check_name_coord2(tmp);
	if(!(first = binary_search(tmp[0], all->number_of_all_rooms, all->arr_rooms)))
		exit(ft_printf("\x1B[31mError, room not found\033[0m ❌ ---> %s", str));
	if(!(second = binary_search(tmp[1], all->number_of_all_rooms, all->arr_rooms)))
		exit(ft_printf("\x1B[31mError, room not found\033[0m ❌ ---> %s", str));
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
			ft_error_str("\x1B[31mError\033[0m");
	}
	!all->arr_rooms ? ft_error_str("\x1B[31mlinks not found\033[0m") : 0;
}
