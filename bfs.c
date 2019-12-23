#include "lem-in.h"

int				bfs(t_all *all)
{
	int			i = 0;
	int			end = 1;
	t_rooms		*read_trooms;
	t_list		*read_tlist;
	unsigned	iterator = 0;

	all->que[i] = all->first_room;
	while(iterator < all->number_of_all_rooms) ///-1??? первая комната уже записана ///que[i] != NULL??
	{
		read_tlist = all->que[i]->links;
		while(read_tlist != NULL)
		{
			read_trooms = read_tlist->content;
			if (read_trooms->lvl != -1)
			{
				if(read_trooms->lvl == INT_MAX)
				{
					all->que[end] = read_trooms;
					all->que[end]->lvl = all->que[i]->lvl + 1;
					return (end);
				}
				read_tlist = read_tlist->next;
				continue;
			}
			all->que[end] = read_tlist->content;
			all->que[end]->lvl = all->que[i]->lvl + 1;
			read_tlist = read_tlist->next;
		 	end++;
		}
		i++;
		iterator++;
	}
	return (0);
}

void		push_path(t_rooms **current, t_rooms *new)
{
	if (current && new)
	{
		if (*current)
			new->next = *current;
		*current = new;
	}
}

int		reverse_path(t_rooms **queue, int end, t_ways *list_ways)
{
	t_rooms *t_reader;
	t_list	*cur_list;

	t_reader = queue[end];
	list_ways->way_t = queue[end];
	cur_list = list_ways->way_t->links;
	while(t_reader->lvl != 0)
	{
		t_reader = cur_list->content;
		if(t_reader->lvl == list_ways->way_t->lvl - 1)
		{
			push_path(&list_ways->way_t, t_reader);
			t_reader->mark = t_reader->lvl != 0 ? 1 : 0;
			if(list_ways->way_t->lvl == 0)
				return (1);
			cur_list = t_reader->links;
		}
		else
			cur_list = cur_list->next;
		//end--;
	}
	return (0);
}
