#include "lem-in.h"

int				bfs(t_all *all)
{
	int			i = 0;
	int			end = 1;
	t_rooms		*read_trooms;
	t_list		*read_tlist;
	unsigned	iterator = 1;

	all->que[i] = all->first_room;
	while (iterator < all->number_of_all_rooms) ///-1??? первая комната уже записана ///que[i] != NULL??
	{
		read_tlist = all->que[i]->links;
		while (read_tlist != NULL)
		{
			read_trooms = read_tlist->content;
			if (read_trooms->lvl != -1)
			{
				if (read_trooms->lvl == 0x7FFFFFFF)
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

void		t_room_add(t_rooms **current, t_rooms *new)
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
	int last;
	int steps;

	last = 1;
	steps = queue[end]->lvl;
	list_ways->way_t = queue[end];
	cur_list = list_ways->way_t->links;
	while (steps > 0)
	{
		while (cur_list->next != NULL)
		{
			t_reader = cur_list->content;
			if (t_reader->lvl == list_ways->way_t->lvl - 1)
			{
				t_room_add(&list_ways->way_t, t_reader);
				cur_list = t_reader->links;
				steps--;
				break ;
			}
			cur_list = cur_list->next;
		}
	}
	return (0);
}
