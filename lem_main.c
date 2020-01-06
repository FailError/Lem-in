/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   lem_main.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: kbessa <kbessa@student.42.fr>  +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2019/11/11 15:05:49 by kbessa#+##+# */
/*   Updated: 2019/12/13 17:26:22 by kbessa   ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "lem-in.h"

t_rooms	*ft_create(char **room) ///создаем комнату->обнуляем->записываем имя и координаты
{
	t_rooms *new;

	new = ft_memalloc(sizeof(t_rooms));
	new->name = room[0];
	if (new->name[0] == 'L')
		ft_error_str("\x1B[31mError, name cannot begin with 'L'\033[0m");
	new->x = ft_atoi_ants(room[1]);
	new->y = ft_atoi_ants(room[2]);
	new->lvl = -1;
	free(room);
	return (new);
}

void	push_v_konec(t_ways **list_ways, t_ways *new)
{
	t_ways *tmp;

	if ((*list_ways)->way_t)
	{
		tmp = *list_ways;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*list_ways = new;
}

int main(int argc, char **argv)
{
	int fd;
	t_all all;
	int end;
	t_ways *list_ways;
	t_ways  *new;

	argc = 0;
	ft_bzero(&all, sizeof(t_all));
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	else
		exit(0);
	number_of_ants(&all, fd);
	all_rooms(&all, fd);
	all.first_room->lvl = 0;
	all.last_room->lvl = INT_MAX;
	all.que = ft_memalloc(sizeof(t_rooms *) * all.number_of_all_rooms + 1);
	list_ways = (t_ways *)ft_memalloc(sizeof(t_ways));
	while ((end = bfs(&all)))
	{
		new = reverse_path(all.que, all.last_room);
		mark_path(new);
		push_v_konec(&list_ways, new);
		zero_lvl(&all);
		zero_que(&all);
	}
	close(fd);
	return (0);
}
