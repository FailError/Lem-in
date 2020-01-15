/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/14 18:01:58 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

t_rooms	*ft_create(char **room) ///создаем комнату->обнуляем->записываем имя и координаты
{
	t_rooms *new;

	new = ft_memalloc(sizeof(t_rooms));
	new->name = room[0];
	if (new->name[0] == 'L')
		ft_error_str("\x1B[31mError, name cannot begin with 'L'\033[0m");
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->lvl = -1;
	int a = 0;
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
	{
		free(*list_ways);
		*list_ways = new;
	}
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
	if(ways->way_t)
	{
		while (w)
		{
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

void		free_arr_rooms_and_links(t_all *all)
{
	t_list	*lol;
	int		i;
	unsigned rooms;

	rooms = all->number_of_all_rooms;
	i = 0;
	while (rooms > 0)
	{
		free(all->arr_rooms[i]->name);
		while (all->arr_rooms[i]->links)
		{
			lol = all->arr_rooms[i]->links->next;
			free(all->arr_rooms[i]->links);
			all->arr_rooms[i]->links = lol;
		}
		free(all->arr_rooms[i]);
		all->arr_rooms[i] = NULL;
		i++;
		rooms--;
	}
	free(all->arr_rooms);
}

void		free_new(t_ways *new)
{
	t_list *lol;
	int i = 0;
	if(new)
	{
		if (new->way_t)
		{
			while (new->way_t)
			{
				lol = new->way_t->next;
				free(new->way_t);
				new->way_t = lol;
			}
			free(new->way_t);
		}
	}
	if(new)
	{
		int j = 0;
		if(new->in_array)
		{
			free(new->in_array);
			new->in_array = NULL;
		}
	}

}

int			main(int argc, char **argv)
{

	int		fd;
	t_all	all;
	t_ways	*list_ways;
	t_ways	*new = NULL;
	t_calc	calc;
	all.arr_rooms = NULL;

	ft_bzero(&calc, sizeof(t_calc));
	argc = 0;
	ft_bzero(&all, sizeof(t_all));
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	else
		exit(0);
//	fd = 0;
	number_of_ants(&all, fd, &calc);
	all_rooms(&all, fd);
	all.que = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * (all.number_of_all_rooms + 1));
	list_ways = (t_ways *)ft_memalloc(sizeof(t_ways));
	while (bfs(&all))
	{
		new = reverse_path(all.last_room);
		calculated(&calc, list_ways);
		if(serch_edge(list_ways, new, &calc))
		{
			free_new(new);
			break;
		}
		else
			push_v_konec(&list_ways, new);
		zero_lvl_que(&all);
	}
	calculated(&calc, list_ways);
	!list_ways->way_t ? error("no ways") : 0;
	ft_printf("\n");
	//print_path(list_ways, &calc);
	ft_printf("Ходов потребуется - %d ->жду %d строк\n", calc.result, calc.result);
	print_pathq(&all, list_ways, &calc);

	free_arr_rooms_and_links(&all); ///работает;
	free(all.que); ///работает

	close(fd);
	exit (0); //return (0);;
}
