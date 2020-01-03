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

void	zero_lvl(t_all *all)
{
	int i;

	i = 1;
	while (all->que[i])
	{
		all->que[i]->lvl = -1;
		i++;
	}
	all->last_room->lvl = INT_MAX;
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
	t_rooms *t_reader = NULL;
	t_rooms *t_reader2 = NULL;
	t_list	*cur_list;
	t_ways *new;
	int steps;

	new = (t_ways *) ft_memalloc(sizeof(t_ways));
	steps = last->lvl; //queue[end]->lvl;
	ft_lstadd(&new->way_t, ft_lstnew2(last));//queue[end]; ///если реверс пути то first //[0]
	new->length++;

	cur_list = last->links;
	while (cur_list)
	{
		t_reader = cur_list->content;///получил *C* теперь ориентируюсь на то что в списке new =);
		if(t_reader->lvl == last->lvl - 1)
			break;
		cur_list = cur_list->next;
	}
 ///--------------^^^закинул ласт вершину и после нее некст, теперь начинаю с предпоследней!!------

	while (steps > 1)
	{
		t_reader2 = new->way_t->content; ///*Z*
		cur_list = t_reader->links; ///линки из *C*
		while (cur_list != NULL)
		{ //пихать сюда че?
			if (t_reader2->lvl == t_reader->lvl + 1) ///если реверс пути то +1
			{
				cur_list->content_size = 1;
				new->length++;
			}
			cur_list = cur_list->next;
		}
		ft_lstadd(&new->way_t, ft_lstnew2(t_reader)); ///что ?
		t_reader2 = new->way_t->content;
		steps--;
	}
	return (new);
}

//void				mark_links(t_ways  *new) //content size = 1 у всех вершин, кроме 1-ой
//{
//	t_rooms		*t_reader;
//	t_list		*cur_list;
//
//	cur_list = new->way_t->next;
//	while(cur_list)
//	{
//		cur_list->content_size = 1;
//		cur_list = cur_list->next;
//	}
//}


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
