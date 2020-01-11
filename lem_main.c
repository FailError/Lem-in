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

void	lst_add_konec(t_list **lst, t_list *newlist)
{
	t_list *tmp;

	if((*lst))
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newlist;
	}
	else
		*lst = newlist;
}

void	push_v_konec(t_ways **list_ways, t_ways *new, t_calc *calc)
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
		if(current_ways->fake)///hmmmmmm....
		{
			current_ways = current_ways->next;
			continue;
		}
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

void obmen(t_ways *list_ways, t_ways *new, t_point *points)
{


}

void		push_v_list(t_ways *w, t_ways *new, t_point *points, t_calc *calc)
{
	t_ways	*new_path = NULL;
	t_list	*list = NULL;
	t_rooms	*read_n = NULL;
	int		i;
	int		a;
	int 	b;
	int		result_new;

	i = 0;
	a = 1;
	b = 1;
	while(ft_strcmp(new->in_array[i++]->name, points->second->name))
		a++;
	i = w->length - 1;
	while(ft_strcmp(w->in_array[i--]->name, points->second->name))
		a++;
///////////////////////////////////////////////////////////////////
	i = 0;
	while(ft_strcmp(w->in_array[i++]->name, points->first->name))
		b++;
	i = new->length - 1;
	while(ft_strcmp(new->in_array[i--]->name, points->first->name))
		b++;
	calc->sum_steps_all_ways = calc->sum_steps_all_ways - w->length - 1 + (a + b);
	calc->number_of_ways = calc->number_of_ways - 1 + 2;

	a = calc->number_of_ants + calc->sum_steps_all_ways;
	b = calc->number_of_ways;
	if (a % b == 0)
		result_new = a / b - 1;
	else
		result_new = a / b;
	///////////////////////////////////////////////////////////
	if(result_new > calc->result)
		return;
	else
	{
		calc->result = result_new;
		w->fake = 1;

		t_ways *new1 = (t_ways *) ft_memalloc(sizeof(t_ways));
		i = 0;
		while(ft_strcmp(new->in_array[i]->name, points->second->name))
		{
			lst_add_konec(&new1->way_t, ft_lstnew2(new->in_array[i]));
			new1->length++;
			i++;
		}
		i = 0;
		while(ft_strcmp(w->in_array[i]->name, points->second->name))
			i++;
		while(w->in_array[i])
		{
			lst_add_konec(&new1->way_t, ft_lstnew2(w->in_array[i]));
			new1->length++;
			i++;
		}
		////////////////////////////////////////////////////////////

		t_ways *new2 = (t_ways *) ft_memalloc(sizeof(t_ways));
		i = 0;
		while(ft_strcmp(w->in_array[i]->name, points->first->name))
		{
			lst_add_konec(&new2->way_t, ft_lstnew2(w->in_array[i]));
			new2->length++;
			i++;
		}
		i = 0;
		while(ft_strcmp(new->in_array[i]->name, points->first->name))
			i++;
		while(new->in_array[i])
		{
			lst_add_konec(&new2->way_t, ft_lstnew2(new->in_array[i]));
			new2->length++;
			i++;
		}
		in_array(new1);
		in_array(new2);
		push_v_konec(&w, new1, calc);
		push_v_konec(&w, new2, calc);
	}
}

void		calculated(t_calc *calc, t_ways *ways)
{
	t_ways	*w = NULL;
	int		a;
	int		b;

	calc->sum_steps_all_ways = 0;
	calc->number_of_ways = 0;


	w = ways;
	if(ways->way_t)
	{
		while (w)
		{
			if(w->fake)///hmmmmmm....
			{
				w = w->next;
				continue;
			}
			calc->sum_steps_all_ways += w->length - 1;
			calc->number_of_ways += 1;
			w = w->next;
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
		new = reverse_path(all.que, all.last_room);
		calculated(&calc, list_ways);
		if(serch_edge(list_ways, new, &calc))
			;
		else
			push_v_konec(&list_ways, new, &calc);
		//calculated(&calc, list_ways);
		zero_lvl_que(&all);
	}
	print_path(list_ways, &calc);
	ft_printf("Ходов потребуется - %d", calc.result);
	close(fd);
	return (0);
}
