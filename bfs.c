#include "lem-in.h"

int 	ft_push(t_queue *queue, t_rooms *room)
{
//	t_rooms *tmp;

	queue->room = room;
//	while(room->links != NULL)
//	{
//		tmp = room;
//	}
}

int 	ft_color(t_queue *queue, t_rooms *room)
{
	static int i = 0;
	while(queue->next != NULL)
	{
		queue->room->lvl = i;
	}
	i++;
}

int 	ft_pop(t_queue *queue, t_rooms *room)///возьми из очереди и разложи новые
{
	t_rooms *tmp;

	queue->room;
}

int 	ft_isempty(t_queue *queue)
{
	if(queue->room == NULL)
		return (1);
	return (0);
}

int		bfs(t_all *all)
{
	int start = 0;
	int end = 1;
	//t_queue queue;
	t_rooms **que;
	t_rooms *rd;
	int i = 0;

	que = (t_rooms **) ft_memalloc(sizeof(t_rooms) * all->number_of_all_rooms);
	que[start] = all->first_room;
	while(i < all->number_of_all_rooms)
	{
		que[end] = que[start]->links->content;
	}




//	ft_push(&queue, all->first_room);
//	ft_color(&queue, all->first_room);

//	while(!ft_isempty(&queue))
//	{
//		ft_pop(&queue, all->first_room); //regewre
//		ft_color(&queue, all->first_room);
//
//	}
	return (0);
}