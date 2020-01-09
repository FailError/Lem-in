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
				{
					read_tlist = read_tlist->next;
				}
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

t_ways		*reverse_path(t_rooms **queue, t_rooms *last)
{
	t_rooms *t_reader = NULL;
	t_rooms *t_reader2 = NULL;
	t_list	*cur_list;
	t_ways *new;
	int steps;

	new = (t_ways *) ft_memalloc(sizeof(t_ways));
	steps = last->lvl; //queue[end]->lvl;
	ft_lstadd(&new->way_t, ft_lstnew2(last));//queue[end]; ///если реверс пути то first //[0]
	new->length++;
	while (steps > 0)
	{
		t_reader = new->way_t->content;
		cur_list = t_reader->links;
		while (cur_list != NULL)
		{
			t_reader2 = cur_list->content;
			if (t_reader2->lvl == t_reader->lvl - 1) ///если реверс пути то +1
			{
				ft_lstadd(&new->way_t, ft_lstnew2(t_reader2));
				new->length++;
				break;
			}
			cur_list = cur_list->next;
		}
		steps--;
	}
	in_array(new);
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
	while(i > 1)
	{
		t_readerFirst = cur_list->content;
		t_readerSecond = cur_list->next->content;
		linki = t_readerFirst->links;
		while (linki != NULL)
		{
			read = linki->content;
			if(strcmp(read->name, t_readerSecond->name) == 0)
				linki->content_size = 1;
			linki = linki->next;
		}
		cur_list = cur_list->next;
		i--;
	}
}

int			serch_dubl(t_ways *list_ways, t_ways *new)
{
	t_ways		*w = NULL;
	t_list		*l = NULL;
	int 		i;
	int			j;
	int 		f = 0;
	int 		tmp;
	int 		number_of_list = 0;
	t_rooms 	**old_arr;
	t_rooms 	**new_arr;

	t_rooms		*first = NULL;
	t_rooms		*second = NULL;

	i = 1;
	j = 1;
	w = list_ways;
	l = list_ways->way_t;
	new_arr = new->in_array;
	old_arr = w->in_array;

	if(list_ways->way_t)
	{
		while(w)
		{
			number_of_list++;
			tmp = w->length - 1 ;
			while (old_arr[i] && new_arr[j])
			{
				while (old_arr[i] && new_arr[j] && tmp != 1)
				{
					if (ft_strcmp(old_arr[i]->name, new_arr[j]->name) == 0 && !f)
					{
						second = new_arr[j];
						f = 1;
					}
					else if (ft_strcmp(old_arr[i]->name, new_arr[j]->name) == 0)
					{

						first = new_arr[j];
					}
					i++;
					tmp--;
				}
				tmp = w->length -1;
				j++;
				i = 1;
			}
			w = w->next;
			i = 1;
			j = 1;
		}
	}
	return (0);
}
