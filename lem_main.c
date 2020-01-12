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

void				print_path(t_ways *ways, t_calc *calc)
{
	t_list	*current_list;
	t_rooms	*current_rooms;
	t_ways	*current_ways;
	int i;

	i = 1;
	current_ways = ways;
	while (current_ways)
	{
		current_list = current_ways->way_t;
		while (current_list)
		{
			current_rooms = current_list->content;
			ft_printf("L%d-%s ",i, current_rooms->name);
			current_list = current_list->next;
		}
		ft_printf("<%d>", current_ways->length - 1);
		ft_printf("\n");
		current_ways = current_ways->next;
		i++;
	}

}

void			in_array(t_ways *new)
{
	t_list		*current_list;
	t_rooms		*current_rooms;
	int			i;

	i = 0;
	new->in_array = ft_memalloc(sizeof(t_rooms *) * (new->length + 1));
	current_list = new->way_t;
	while (current_list)
	{
		current_rooms = current_list->content;
		new->in_array[i] = current_rooms;
		current_list = current_list->next;
		i++;
	}
}

void		calculated(t_calc *calc, t_ways *ways)
{
	t_ways	*w = NULL;
	int		a;
	int		b;
	int		i;

	calc->sum_steps_all_ways = 0;
	calc->number_of_ways = 0;
	w = ways;
	i = 1;
	w->path_no = i;
	if(ways->way_t)
	{
		while (w)
		{

			w->path_no = i;
			calc->sum_steps_all_ways += w->length - 1;
			calc->number_of_ways += 1;
			w = w->next;
			i++;
		}
		a = calc->number_of_ants + calc->sum_steps_all_ways;
		b = calc->number_of_ways;
		if (a % b == 0)
			calc->result = a / b - 1;
		else
			calc->result = a / b;
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	t_all	all;
	t_ways	*list_ways;
	t_ways	*new;
	t_calc	calc;

	ft_bzero(&calc, sizeof(t_calc));
	argc = 0;
	ft_bzero(&all, sizeof(t_all));
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	else
		exit(0);
	number_of_ants(&all, fd, &calc);
	all_rooms(&all, fd);
	all.que = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * (all.number_of_all_rooms + 1));
	list_ways = (t_ways *)ft_memalloc(sizeof(t_ways));
	while (bfs(&all))
	{
		new = reverse_path(all.last_room);
		calculated(&calc, list_ways);
		if(serch_edge(list_ways, new, &calc))
			;
		else
			push_v_konec(&list_ways, new);
		zero_lvl_que(&all);
	}
	calculated(&calc, list_ways);
	!list_ways->way_t ? ft_putstr("no ways") : 0;
	ft_printf("\n");
	print_path(list_ways, &calc);
	ft_printf("Ходов потребуется - %d", calc.result);

	//print_pathq(&all, list_ways);
	close(fd);
	return (0);
}
