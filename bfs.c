/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:01:15 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 21:11:58 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		bfs_lvlup(t_all *all, t_list **read_tlist, unsigned *start)
{
	t_rooms		*read_trooms;

	read_trooms = (*read_tlist)->content;
	if (read_trooms->lvl == -1 || read_trooms->lvl == INT_MAX)
	{
		if (read_trooms->lvl == INT_MAX)
			all->success = 1;
		all->que[all->end] = (*read_tlist)->content;
		all->que[all->end]->lvl = all->que[*start]->lvl + 1;
		*read_tlist = (*read_tlist)->next;
		all->end++;
	}
	else
		*read_tlist = (*read_tlist)->next;
}

int				bfs(t_all *all)
{
	unsigned	start;
	t_list		*read_tlist;

	start = 0;
	all->que[start] = all->first_room;
	all->success = 0;
	all->end = 1;
	while (start < all->n_rooms)
	{
		if (all->que[start])
		{
			read_tlist = all->que[start]->links;
			while (read_tlist != NULL)
			{
				if (read_tlist->content_size == 1)
					read_tlist = read_tlist->next;
				else
					bfs_lvlup(all, &read_tlist, &start);
			}
			start++;
		}
		else
			return (all->success);
	}
	return (all->success);
}

int				room_doublicate(t_ways *w, t_ways *new, t_rooms **new_arr)
{
	int			i;
	int			j;
	t_rooms		**old_arr;

	j = 1;
	old_arr = w->in_array;
	while (j < new->length - 1)
	{
		i = 1;
		while (i < w->length - 1)
		{
			if (ft_strcmp(old_arr[i]->name, new_arr[j]->name) == 0)
				return (1);
			i++;
		}
		j += 1;
	}
	return (0);
}

int				serch_edge(t_ways *ways, t_ways *new, t_calc *calc,
					t_rooms *first)
{
	t_ways		*w;
	t_rooms		**new_arr;

	w = ways;
	new_arr = new->in_array;
	if (ft_strcmp(new->in_array[0]->name, first->name) == 0)
		return (0);
	if (ways->way_t)
	{
		while (w)
		{
			if (room_doublicate(w, new, new_arr))
				return (1);
			w = w->next;
		}
		if (new_calc(calc, new))
			return (1);
	}
	return (0);
}

int				new_calc(t_calc *calc, t_ways *new)
{
	int			a;
	int			b;
	int			newresult;
	int			success;

	a = calc->number_of_ants + calc->sum_steps_all_ways + new->length - 1;
	b = calc->number_of_ways + 1;
	if (a % b == 0)
		newresult = a / b - 1;
	else
		newresult = a / b;
	success = newresult > calc->result ? 1 : 0;
	return (success);
}
