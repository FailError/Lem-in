/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 22:08:43 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 22:31:28 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ways			*initial(t_rooms *last)
{
	t_ways		*new;

	new = (t_ways *)ft_memalloc(sizeof(t_ways));
	ft_lstadd(&new->way_t, ft_lstnew2(last));
	new->steps = last->lvl;
	new->length++;
	return (new);
}

int				search_room(t_rooms *t_reader, t_rooms *t_reader2, t_ways *new,
									t_rooms *first)
{
	if ((t_reader2->lvl == t_reader->lvl - 1 && !t_reader2->wputi) ||
		ft_strcmp(first->name, t_reader2->name) == 0)
	{
		t_reader2->wputi = 1;
		ft_lstadd(&new->way_t, ft_lstnew2(t_reader2));
		new->length++;
		return (1);
	}
	return (0);
}

t_ways			*reverse_path(t_rooms *last, t_rooms *first)
{
	t_rooms		*t_reader;
	t_rooms		*t_reader2;
	t_list		*cur_list;
	t_ways		*new;

	new = initial(last);
	while (new->steps > 0)
	{
		t_reader = new->way_t->content;
		cur_list = t_reader->links;
		while (cur_list != NULL)
		{
			t_reader2 = cur_list->content;
			if (search_room(t_reader, t_reader2, new, first))
				break ;
			cur_list = cur_list->next;
		}
		new->steps--;
	}
	in_array(new);
	mark_path(new);
	return (new);
}

void			in_array(t_ways *new)
{
	t_list		*current_list;
	t_rooms		*current_rooms;
	int			i;

	i = 0;
	new->in_array = ft_memalloc(sizeof(t_rooms *) * (new->length + 1));
	current_list = new->way_t;
	while (current_list)
	{
		current_rooms = current_list->content;
		new->in_array[i] = current_rooms;
		current_list = current_list->next;
		i++;
	}
}

void			mark_path(t_ways *new)
{
	t_rooms		*t_readerfirst;
	t_rooms		*t_readersecond;
	t_list		*cur_list;
	t_rooms		*read;
	t_list		*linki;

	new->steps = new->length;
	cur_list = new->way_t;
	while (new->steps > 1)
	{
		t_readerfirst = cur_list->content;
		t_readersecond = cur_list->next->content;
		linki = t_readerfirst->links;
		while (linki != NULL)
		{
			read = linki->content;
			if (strcmp(read->name, t_readersecond->name) == 0)
				linki->content_size = 1;
			linki = linki->next;
		}
		cur_list = cur_list->next;
		new->steps--;
	}
}
