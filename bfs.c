#include "lem-in.h"

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

void 				print_pathq(t_all *all, t_ways *ways)
{
	t_ways *w;
	unsigned ants = all->number_of_ants;

	w = ways;
	int i = 0;
	while(all->last_room->ant_n != all->number_of_ants)
	{
		while(w)
		{
			w = w->next;
		}
	}
}

