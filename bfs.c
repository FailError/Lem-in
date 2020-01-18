/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:01:15 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/15 21:20:00 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list			*ft_lstnew2(void const *content)
{
	t_list		*newl;

	if (!(newl = (t_list *)ft_memalloc(sizeof(*newl))))
		return (NULL);
	if (content == NULL)
	{
		newl->content = NULL;
		newl->content_size = 0;
	}
	else
	{
		newl->content = (void *)content;
		newl->content_size = sizeof(void *);
	}
	newl->next = NULL;
	return (newl);
}

static void		bfs_lvlup(t_all *all, t_list **read_tlist, const int *start)
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
	int			start;
	t_list		*read_tlist;

	start = 0;
	all->que[start] = all->first_room;
	all->success = 0;
	all->end = 1;
	while (start < all->num_all_rooms)
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

void			zero_lvl_que(t_all *all)
{
	int			i;
	int			j;

	j = 0;
	i = 1;
	while (all->que[i])
	{
		all->que[i]->lvl = -1;
		i++;
	}
	while (all->que[j])
	{
		all->que[j] = NULL;
		j++;
	}
	all->last_room->lvl = INT_MAX;
}

t_ways			*initial(t_ways *new, t_rooms *last)
{
	new = (t_ways *)ft_memalloc(sizeof(t_ways));
	ft_lstadd(&new->way_t, ft_lstnew2(last));
	new->steps = last->lvl;
	new->length++;
	return (new);
}

int				search_room(t_rooms *t_reader, t_rooms *t_reader2, t_ways *new,
				t_rooms *first)
{
	if ((t_reader2->lvl == t_reader->lvl - 1 && !t_reader2->wputi) ||
		ft_strcmp(first->name, t_reader2->name) == 0)
	{
		t_reader2->wputi = 1;
		ft_lstadd(&new->way_t, ft_lstnew2(t_reader2));
		new->length++;
		return (1);
	}
	return (0);
}

t_ways			*reverse_path(t_rooms *last, t_rooms *first)
{
	t_rooms		*t_reader;
	t_rooms		*t_reader2;
	t_list		*cur_list;
	t_ways		*new;

	new = initial(new, last);
	while (new->steps > 0)
	{
		t_reader = new->way_t->content;
		cur_list = t_reader->links;
		while (cur_list != NULL)
		{
			t_reader2 = cur_list->content;
			if (search_room(t_reader, t_reader2, new, first))
				break ;
			cur_list = cur_list->next;
		}
		new->steps--;
	}
	in_array(new);
	mark_path(new);
	return (new);
}

void			mark_path(t_ways *new)
{
	t_rooms		*t_readerfirst;
	t_rooms		*t_readersecond;
	t_list		*cur_list;
	t_rooms		*read;
	t_list		*linki;

	new->steps = new->length;
	cur_list = new->way_t;
	while (new->steps > 1)
	{
		t_readerfirst = cur_list->content;
		t_readersecond = cur_list->next->content;
		linki = t_readerfirst->links;
		while (linki != NULL)
		{
			read = linki->content;
			if (strcmp(read->name, t_readersecond->name) == 0)
				linki->content_size = 1;
			linki = linki->next;
		}
		cur_list = cur_list->next;
		new->steps--;
	}
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

t_ways			**final_map_to_arr(t_ways *ways, t_calc *calc)
{
	int			i;
	t_ways		*w;
	t_ways		**new;

	new = (t_ways **)ft_memalloc(sizeof(t_ways *) * (calc->number_of_ways + 1));
	w = ways;
	i = 0;
	while (w)
	{
		new[i] = w;
		w = w->next;
		i++;
	}
	return (new);
}

void			expression(t_ways **arr_p)
{
	int			i;
	int			j;
	int			current_l;
	int			prev_l;

	i = 0;
	j = 1;
	current_l = 0;
	prev_l = 0;
	while (arr_p[j])
	{
		while (i != j)
		{
			prev_l += arr_p[i]->length - 1;
			current_l += arr_p[j]->length - 1;
			i++;
		}
		arr_p[j]->expression = current_l - prev_l;
		current_l = 0;
		prev_l = 0;
		j++;
		i = 0;
	}
}

void			for_len_2(t_ways *arr, int *ants_ostatok, int *ants_current)
{
	ft_printf("L%d-%s ", *ants_current, arr->in_array[1]->name);
	arr->in_array[1]->itogo++;
	*ants_ostatok -= 1;
	*ants_current += 1;
}

void			going_to_last_room(t_ways *arr)
{
	ft_printf("L%d-%s ", arr->in_array[arr->length - 2]->ant_n,
		arr->in_array[arr->length - 1]->name);
	arr->in_array[arr->length - 1]->itogo++;
	arr->in_array[arr->length - 2]->ant_n = 0;
}

void			going_to_next_room(t_ways *arr, int *last)
{
	arr->in_array[*last + 1]->ant_n = arr->in_array[*last]->ant_n;
	ft_printf("L%d-%s ", arr->in_array[*last]->ant_n,
		arr->in_array[*last + 1]->name);
	arr->in_array[*last]->ant_n = 0;
	*last -= 1;
}

void			walkind_ants(t_ways *arr, int *ants_ostatok, int *ants_current)
{
	int			last;

	last = arr->length - 3;
	if (arr->length == 2 && *ants_ostatok > arr->expression)
		for_len_2(arr, ants_ostatok, ants_current);
	else
	{
		if (arr->in_array[arr->length - 2]->ant_n)
			going_to_last_room(arr);
		while (last != 0)
		{
			if (arr->in_array[last]->ant_n)
				going_to_next_room(arr, &last);
			else
				last--;
		}
		if (*ants_ostatok > arr->expression)
		{
			arr->in_array[1]->ant_n = *ants_current;
			ft_printf("L%d-%s ", *ants_current, arr->in_array[1]->name);
			*ants_ostatok -= 1;
			*ants_current += 1;
		}
	}
}

void			print_path(t_all *all, t_ways *ways, t_calc *calc)
{
	int			ants_ostatok;
	int			ants_current;
	t_ways		**arr_p;
	int			i;

	i = 0;
	ants_ostatok = (int)all->number_of_ants;
	ants_current = 1;
	arr_p = final_map_to_arr(ways, calc);
	expression(arr_p);
	while (all->last_room->itogo != all->number_of_ants)
	{
		while (arr_p[i])
		{
			walkind_ants(arr_p[i], &ants_ostatok, &ants_current);
			i++;
		}
		ft_printf("\n");
		i = 0;
	}
	free(arr_p);
}
