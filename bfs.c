#include "lem-in.h"

int				bfs(t_all *all)
{
	int			i = 0;
	int			end = 1;
	t_rooms		*read_trooms;
	t_list		*read_tlist;
	int			success = 0;

	all->que[i] = all->first_room;
	while (i < all->number_of_all_rooms)
	{
		read_tlist = all->que[i]->links;
		while (read_tlist != NULL)
		{
			read_trooms = read_tlist->content;
			if (read_trooms->lvl == -1 || read_trooms->lvl == INT_MAX)
			{
				if (read_trooms->lvl == INT_MAX)
				{
					success = 1;
					all->list_of_rooms = read_tlist;
				}
				all->que[end] = read_tlist->content;
				all->que[end]->lvl = all->que[i]->lvl + 1;
				read_tlist = read_tlist->next;
				end++;
			}
			else
				read_tlist = read_tlist->next;
		}
		i++;
	}
	return (success);
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

void	zero_lvl(t_rooms **que, int end)
{
	int i;

	i = 1;
	while (i < end)
	{
		que[i]->lvl = -1;
		i++;
	}
	que[i]->lvl = 0x7FFFFFFF;
}

void        zero_que(t_all *all)
{
    int i = 0;
    while (all->que[i])
	{
		all->que[i] = NULL;
		i++;
	}
}

t_ways		*reverse_path(t_rooms **queue, t_rooms *last, t_list *t_lst) //t_lst - ласт комната
{
	t_rooms *t_reader;
	t_list	*cur_list;
	t_ways *new;
	int steps;

	new = (t_ways *) ft_memalloc(sizeof(t_ways));
	steps = last->lvl; //queue[end]->lvl;
	new->way_t = last;//queue[end]; ///если реверс пути то first //[0]
	new->way_t->mark = 1;
	new->length++;
	cur_list = new->way_t->links;
	while (steps > 0)
	{
		while (cur_list != NULL)
		{
			t_reader = cur_list->content;
			if (t_reader->lvl == new->way_t->lvl - 1) ///если реверс пути то +1
			{
			    t_reader->mark = 1;
				new->length++;
				t_room_add(&new->way_t, t_reader);
				cur_list = t_reader->links;
				steps--;
				break ;
			}
			cur_list = cur_list->next;
		}
	}
	return (new);
}

//void				delete_links(t_ways *list_ways)
//{
//	t_rooms *current;
//	t_rooms *deleted;
//	t_rooms *tmp;
//
//	current = list_ways->way_t;
//	tmp = current->links->content;
//	while(current->next != NULL)
//	{
//		deleted = current->next;
//		while(tmp->links->next)
//		{
//			if(!ft_strcmp(deleted->name, tmp->name))
//
//		}
//
//		current = current->next;
//	}
//}
