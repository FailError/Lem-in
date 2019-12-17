#include "lem-in.h"

int		bfs(t_all *all)
{
	int start = 0;
	int end = 1;
	//t_queue queue;
	t_rooms **que;
	t_rooms *rd;
	t_list *rf;
	int i = 0;
	int lvl = 1;

	que = ft_memalloc(sizeof(t_rooms *) * all->number_of_all_rooms);
	que[start] = all->first_room;
	while(i < all->number_of_all_rooms)
	{
		while(que[start]->links->next != NULL)
		{
			rf = que[start]->links;
			rd = que[start]->links->content;
			que[end] = que[start]->links->content;

			que[end]->lvl = lvl;
			rf = que[start]->links->next;
			end++;
		}
		start++;
	}





	return (0);
}