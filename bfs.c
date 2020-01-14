/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:01:15 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/14 18:01:19 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_error_str(char *str)
{
	ft_putstr(str);
	exit(-1);
}

t_list	*ft_lstnew2(void const *content)
{
	t_list	*newl;

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

int				bfs(t_all *all)
{
	int			i = 0;
	int			end = 1;
	t_rooms		*read_trooms = NULL;
	t_list		*read_tlist = NULL;
	int			success = 0;

	all->que[i] = all->first_room;
	while (i < all->number_of_all_rooms)
	{
		if (all->que[i])
		{
			read_tlist = all->que[i]->links;
			while (read_tlist != NULL)
			{
				if (read_tlist->content_size == 1)
					read_tlist = read_tlist->next;
				else
				{
					read_trooms = read_tlist->content;
					if (read_trooms->lvl == -1 || read_trooms->lvl == INT_MAX)
					{
						if (read_trooms->lvl == INT_MAX)
							success = 1;
						all->que[end] = read_tlist->content;
						all->que[end]->lvl = all->que[i]->lvl + 1;
						read_tlist = read_tlist->next;
						end++;
					}
					else
						read_tlist = read_tlist->next;
				}
			}
			i++;
		}
		else
			return (success);
	}
	return (success);
}

void	zero_lvl_que(t_all *all)
{
	int i;
	int j;

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

t_ways		*reverse_path(t_rooms *last)
{
	t_rooms *t_reader = NULL;
	t_rooms *t_reader2 = NULL;
	t_list	*cur_list;
	t_ways *new;
	int steps;
	static int num = 1;

	new = (t_ways *) ft_memalloc(sizeof(t_ways));
	steps = last->lvl;
	ft_lstadd(&new->way_t, ft_lstnew2(last));
	new->length++;
	while (steps > 0)
	{
		t_reader = new->way_t->content;
		cur_list = t_reader->links;
		while (cur_list != NULL)
		{
			t_reader2 = cur_list->content;
			if (t_reader2->lvl == t_reader->lvl - 1)
			{
				ft_lstadd(&new->way_t, ft_lstnew2(t_reader2));
				new->length++;
				break;
			}
			cur_list = cur_list->next;
		}
		steps--;
	}
	num++;
	in_array(new);
	mark_path(new);
	return (new);
}

void				mark_path(t_ways  *new)
{
	t_rooms		*t_readerFirst = NULL;
	t_rooms		*t_readerSecond = NULL;
	t_list		*cur_list = NULL;
	t_rooms		*read = NULL;
	int			i = new->length;
	t_list		*linki;

	cur_list = new->way_t;
	while (i > 1)
	{
		t_readerFirst = cur_list->content;
		t_readerSecond = cur_list->next->content;
		linki = t_readerFirst->links;
		while (linki != NULL)
		{
			read = linki->content;
			if (strcmp(read->name, t_readerSecond->name) == 0)
				linki->content_size = 1;
			linki = linki->next;
		}
		cur_list = cur_list->next;
		i--;
	}
}

int				serch_edge(t_ways *ways, t_ways *new, t_calc *calc)
{
	t_ways		*w = NULL;
	int 		i;
	int			j;
	int 		tmp;
	t_rooms 	**old_arr = NULL;
	t_rooms 	**new_arr = NULL;
	t_point		points;
	ft_bzero(&points, sizeof(t_point));

	i = 1;
	j = 1;
	w = ways;
	new_arr = new->in_array;

	if (ways->way_t)
	{
		while (w)
		{
			old_arr = w->in_array;
			points.number_of_list++;
			tmp = w->length - 1 ;
			while (old_arr[i] && new_arr[j])
			{
				while (old_arr[i] && new_arr[j] && tmp != 1)
				{
					if (ft_strcmp(old_arr[i]->name, new_arr[j]->name) == 0 && !points.second)
						points.second = new_arr[j];
					if (ft_strcmp(old_arr[i]->name, new_arr[j]->name) == 0 && points.second)
						points.first = new_arr[j];
					i++;
					tmp--;
				}
				tmp = w->length - 1;
				j++;
				i = 1;
			}
			if(points.first || points.second)
				return 1;
			{
				w = w->next;
				i = 1;
				j = 1;
			}
		}
		if(new_calc(calc, new))
			return (1);
	}
	return (0);
}

int		new_calc(t_calc *calc, t_ways *new)
{
	int a;
	int b;
	int newresult;
	int success;

	a = calc->number_of_ants + calc->sum_steps_all_ways + new->length - 1;
	b = calc->number_of_ways + 1;
	if (a % b == 0)
		newresult = a / b - 1;
	else
		newresult = a / b;
	success =  newresult > calc->result ? 1 : 0;
	return (success);
}

t_ways				**final_map_to_arr(t_ways *ways, t_calc *calc)
{
	int i;
	t_ways *w;
	t_ways **new;

	new = (t_ways **)ft_memalloc(sizeof(t_ways *) * (calc->number_of_ways + 1));
	w = ways;
	i = 0;
	while(w)
	{
		new[i] = w;
		w = w->next;
		i++;
	}
	return (new);
}

void				expression(t_ways **arr_p)
{
	int i;
	int j;
	int current_l = 0;
	int prev_l = 0;
	i = 0;
	j = 1;
	while(arr_p[j])
	{
		while(i != j)
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

void	for_len_2(t_ways *arr, int *ants_ostatok, int *ants_current)
{
	ft_printf("L%d-%s ", *ants_current, arr->in_array[1]->name);
	arr->in_array[1]->itogo++;
	*ants_ostatok -= 1;
	*ants_current += 1;
}

void 	walkind_ants(t_ways *arr, int *ants_ostatok, int *ants_current)
{
	int last = arr->length - 3;
	if(arr->length == 2 && *ants_ostatok > arr->expression)
		for_len_2(arr, ants_ostatok, ants_current);
	else
	{
		if(arr->in_array[arr->length - 2]->ant_n)
		{
			ft_printf("L%d-%s ", arr->in_array[arr->length - 2]->ant_n, arr->in_array[arr->length - 1]->name);
			arr->in_array[arr->length - 1]->itogo++;
			arr->in_array[arr->length - 2]->ant_n = 0;

		}
		while(last != 0)
		{
			if(arr->in_array[last]->ant_n)
			{
				arr->in_array[last + 1]->ant_n = arr->in_array[last]->ant_n;
				ft_printf("L%d-%s ",arr->in_array[last]->ant_n, arr->in_array[last + 1]->name);
				arr->in_array[last]->ant_n = 0;
				last--;
			}
			else
				last--;
		}
		if(*ants_ostatok > arr->expression)
		{
			arr->in_array[1]->ant_n = *ants_current;
			ft_printf("L%d-%s ", *ants_current, arr->in_array[1]->name);
			*ants_ostatok -= 1;
			*ants_current += 1;
		}
	}
}

void				freearrp(t_ways **arr)
{
	int iii;

	iii = 0;
	while(arr[iii])
	{
		free(arr[iii]);
		iii++;
	}
	free(*arr);
}

void 				print_pathq(t_all *all, t_ways *ways, t_calc *calc)
{
	int ants_ostatok;
	int ants_current;
	t_ways **arr_p;
	int i;

	i = 0;
	ants_ostatok = (int)all->number_of_ants;
	ants_current = 1;
	arr_p = final_map_to_arr(ways, calc);
	expression(arr_p);
	while(all->last_room->itogo != all->number_of_ants)
	{
		while(arr_p[i])
		{
			walkind_ants(arr_p[i], &ants_ostatok, &ants_current);
			i++;
		}
		ft_printf("\n");
		i = 0;
	}
	free(arr_p); ///вроде работает

}


