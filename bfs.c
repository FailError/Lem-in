#include "lem-in.h"

int			bfs(t_all *all)
{
	int		i = 0;
	int		end = 1;
//	t_rooms	**que;
	t_rooms	*read_trooms;
	t_list	*read_tlist;
	int		iterator = 0;

//	que = ft_memalloc(sizeof(t_rooms *) * all->number_of_all_rooms); //вынести в структуру и выделять память один раз в мейне
	all->que[i] = all->first_room;
	while(iterator < all->number_of_all_rooms)
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

void		reverse_path(t_rooms **queue, int a, t_ways *ways)
{

}
