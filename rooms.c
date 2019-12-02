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
	i > 3 ? ft_error_str("more than two coordinats") : 0;
	i == 2 ? ft_error_str("not all coordinats") : 0;
	i == 1 ? ft_error_str("only one room") : 0;
}

void	ft_start(t_all *all, int fd, char *str)
{
	char **room;

	room = NULL;
	all->first_room ? ft_error_str("double start") : 0;
	while (get_next_line(fd, &str) && ifcomments(str))
	{
	}
	ft_printf("%s\n", str);
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("don't have a room");
	free(str);
	all->first_room = ft_create(room);
	all->numbers_of_rooms++;
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
	all->numbers_of_rooms++;
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

void		if_room_coord(t_all *all, char *str)
{
	char	**room;
	t_rooms	*temp;

	room = NULL;
	room = ft_strsplit(str, ' ');
	room ? check_name_coord(room) : ft_error_str("dont have a room");
	free(str);
	temp = ft_create(room);
	all->numbers_of_rooms++;
	ft_lstadd(&all->list_of_rooms, ft_lstnew_ptr(temp));
}

void	all_rooms(t_all *all, int fd)
{
	char	*str;

	str = NULL;
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		if (ifcomments(str))
			continue;
		else if (start_end(all, fd, str))
			continue;
		else if (ft_strchr(str, ' '))
			if_room_coord(all, str);
	}
}
