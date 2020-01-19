/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:43:25 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 22:28:31 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_arr_rooms_and_links(t_all *all)
{
	t_list		*lol;
	int			i;
	unsigned	rooms;

	rooms = all->n_rooms;
	i = 0;
	while (rooms > 0)
	{
		free(all->ar_room[i]->name);
		while (all->ar_room[i]->links)
		{
			lol = all->ar_room[i]->links->next;
			free(all->ar_room[i]->links);
			all->ar_room[i]->links = lol;
		}
		free(all->ar_room[i]);
		all->ar_room[i] = NULL;
		i++;
		rooms--;
	}
	free(all->ar_room);
}

void			free_new(t_ways *new)
{
	t_list		*lol;

	if (new)
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
	if (new)
	{
		if (new->in_array)
			free(new->in_array);
	}
}

void			next_list(t_ways **list_ways)
{
	t_ways *w;
	t_ways *to_delete;

	w = *list_ways;
	while (w && w->next)
	{
		if (ft_strcmp(w->in_array[0]->name, w->next->in_array[0]->name) == 0)
			w = w->next;
		else
		{
			to_delete = w->next;
			w->next = w->next->next;
			free_new(to_delete);
			free(to_delete);
		}
	}
}

static void		printflags(t_calc *calc, char **argv, t_ways *list_ways)
{
	if (argv[1] && ft_strcmp(argv[1], "-s") == 0)
		ft_printf("\x1B[34mВсего строк: %d\033[0m\n", calc->str_sum);
	else if (argv[1] && ft_strcmp(argv[1], "-p") == 0)
		print_path_length(list_ways);
	if (argv[2] && ft_strcmp(argv[2], "-p") == 0)
		print_path_length(list_ways);
	else if (argv[2] && ft_strcmp(argv[2], "-s") == 0)
		ft_printf("\x1B[34mВсего строк: %d\033[0m\n", calc->str_sum);
}

void			output_and_free(t_all *all, t_ways *list_ways, t_calc *calc,
									char **argv)
{
	t_ways *tmp;

	!list_ways->way_t ? error("no ways") : ft_printf("\n");
	next_list(&list_ways);
	calculated(calc, list_ways);
	print_path(all, list_ways, calc);
	printflags(calc, argv, list_ways);
	free_arr_rooms_and_links(all);
	while (list_ways)
	{
		tmp = list_ways->next;
		free_new(list_ways);
		free(list_ways);
		list_ways = tmp;
	}
	free(all->que);
}
