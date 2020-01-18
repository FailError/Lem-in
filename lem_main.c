/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 22:29:47 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			calculated(t_calc *calc, t_ways *ways)
{
	t_ways		*w;
	int			a;
	int			b;
	int			i;

	calc->sum_steps_all_ways = 0;
	calc->number_of_ways = 0;
	w = ways;
	i = 1;
	if (ways->way_t)
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

void			print_path_length(t_ways *ways)
{
	t_list		*current_list;
	t_rooms		*current_rooms;
	t_ways		*current_ways;
	int			i;

	i = 1;
	current_ways = ways;
	ft_putstr("\033[01;38;05;97m***************************\033[0m");
	while (current_ways)
	{
		current_list = current_ways->way_t;
		while (current_list)
		{
			current_rooms = current_list->content;
			ft_printf("L%d-%s ", i, current_rooms->name);
			current_list = current_list->next;
		}
		ft_printf("<%d>", current_ways->length - 1);
		ft_printf("\n");
		current_ways = current_ways->next;
		i++;
	}
	ft_putstr("\033[01;38;05;97m***************************\033[0m");
}

void			push_v_konec(t_ways **list_ways, t_ways *new)
{
	t_ways		*tmp;

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

static void		init(t_calc *calc, t_ways **list_ways, t_all *all)
{
	ft_bzero(calc, sizeof(t_calc));
	ft_bzero(all, sizeof(t_all));
	*list_ways = (t_ways *)ft_memalloc(sizeof(t_ways));
}

int				main(int argc, char **argv)
{
	t_all		all;
	t_ways		*list_ways;
	t_ways		*new;
	t_calc		calc;

	(void)argc;
	init(&calc, &list_ways, &all);
	number_of_ants(&all, 0, &calc);
	all_rooms(&all, 0);
	all.que = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * (all.n_rooms + 1));
	while (bfs(&all))
	{
		new = reverse_path(all.last_room, all.first_room);
		calculated(&calc, list_ways);
		if (serch_edge(list_ways, new, &calc, all.first_room))
		{
			free_new(new);
			continue;
		}
		else
			push_v_konec(&list_ways, new);
		zero_lvl_que(&all);
	}
	output_and_free(&all, list_ways, &calc, argv);
	exit(0);
}
