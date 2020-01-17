/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/15 21:20:50 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms			*ft_create(char **room)
{
	t_rooms		*new;

	new = ft_memalloc(sizeof(t_rooms));
	new->name = room[0];
	if (new->name[0] == 'L')
		error("Error, name cannot begin with 'L'");
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->lvl = -1;
	free(room);
	return (new);
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

void			free_arr_rooms_and_links(t_all *all)
{
	t_list		*lol;
	int			i;
	unsigned	rooms;

	rooms = all->num_all_rooms;
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

static void		print_path_length(t_ways *ways)
{
	t_list		*current_list;
	t_rooms		*current_rooms;
	t_ways		*current_ways;
	int			i;

	i = 1;
	current_ways = ways;
	ft_putstr("\033[01;38;05;97m❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄\033[0m");
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
	ft_putstr("\033[01;38;05;97m❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄❐▄\033[0m");
}

static void		printflags(t_calc *calc, char **argv, t_ways *list_ways)
{
	if (argv[1] && ft_strcmp(argv[1], "-s") == 0)
		ft_printf("\x1B[34mВсего строк: %d\033[0m\n", calc->result);
	else if (argv[1] && ft_strcmp(argv[1], "-p") == 0)
		print_path_length(list_ways);
	if (argv[2] && ft_strcmp(argv[2], "-p") == 0)
		print_path_length(list_ways);
	else if (argv[2] && ft_strcmp(argv[2], "-s") == 0)
		ft_printf("\x1B[34mВсего строк: %d\033[0m\n", calc->result);
}

static void		init(t_calc *calc, t_ways **list_ways, t_all *all)
{
	ft_bzero(calc, sizeof(t_calc));
	ft_bzero(all, sizeof(t_all));
	*list_ways = (t_ways *)ft_memalloc(sizeof(t_ways));
}

static void		output_and_free(t_all *all, t_ways *list_ways, t_calc *calc,
							char **argv)
{
	calculated(calc, list_ways);
	!list_ways->way_t ? error("no ways") : ft_printf("\n");
	printflags(calc, argv, list_ways);
	print_path(all, list_ways, calc);
	printflags(calc, argv, list_ways);
	free_arr_rooms_and_links(all);
	free(all->que);
}

int				main(int argc, char **argv)
{
	t_all		all;
	t_ways		*list_ways;
	t_ways		*new;
	t_calc		calc;

	init(&calc, &list_ways, &all);
	int fd = open(argv[1], O_RDONLY);
	number_of_ants(&all, fd, &calc);
	all_rooms(&all, fd);
	all.que = (t_rooms **)ft_memalloc(sizeof(t_rooms *) *
	(all.num_all_rooms + 1));
	while (bfs(&all))
	{
		new = reverse_path(all.last_room, all.first_room);
		calculated(&calc, list_ways);
		if (serch_edge(list_ways, new, &calc))
		{
			free_new(new);
			break ;
		}
		else
			push_v_konec(&list_ways, new);
		zero_lvl_que(&all);
	}
	output_and_free(&all, list_ways, &calc, argv);
	exit(0);
}
