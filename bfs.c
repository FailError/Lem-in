#include "lem-in.h"

int		bfs(t_all *all)
{
	int i = 0;
	int end = 1;
	//t_queue queue;
	t_rooms **que;
	t_rooms *read_trooms;
	t_list *read_tlist;
	int tmp = 0;
	int lvl = 1;

	que = ft_memalloc(sizeof(t_rooms *) * all->number_of_all_rooms);
	que[i] = all->first_room;
	while(tmp < all->number_of_all_rooms)
	{
		read_tlist = que[i]->links;
		while(read_tlist != NULL)
		{
			read_trooms = read_tlist->content;

			que[end] = read_tlist->content;
			que[end]->lvl = que[i]->lvl + 1;
			read_tlist = read_tlist->next;
		 	end++;
		}
		i++;
	}
	return (0);
}