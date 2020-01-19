/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:01:05 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 22:29:57 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			zero_lvl_que(t_all *all)
{
	int			i;
	int			j;

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

t_rooms			*ft_create(char **room)
{
	t_rooms		*new;

	new = ft_memalloc(sizeof(t_rooms));
	new->name = room[0];
	if (new->name[0] == 'L')
		error("Error, name cannot begin with 'L'");
	new->x = ft_atoi(room[1]);
	new->y = ft_atoi(room[2]);
	new->lvl = -1;
	free(room);
	return (new);
}

t_list			*ft_lstnew2(void const *content)
{
	t_list		*newl;

	if (!(newl = (t_list *)ft_memalloc(sizeof(*newl))))
		return (NULL);
	if (content == NULL)
	{
		newl->content = NULL;
		newl->content_size = 0;
	}
	else
	{
		newl->content = (void *)content;
		newl->content_size = sizeof(void *);
	}
	newl->next = NULL;
	return (newl);
}

unsigned		ft_atoi_ants(char *str)
{
	unsigned	ants;
	unsigned	i;

	ants = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			ants = (ants * 10) + str[i] - '0';
			i++;
		}
		else
			error("Error, no ants or invalid number-> [1 - INT_MAX]");
	}
	if (ants == 0x0 || i == 0x0 || i > 0xA || ants > 0x7FFFFFFF)
		error("Error, valid number -> [1 - INT_MAX]");
	free(str);
	return (ants);
}

void			number_of_ants(t_all *all, int fd, t_calc *calc)
{
	char		*str;

	str = NULL;
	while(get_next_line(fd, &str))
	{
		if (ft_strcmp(str, "##start") == 0 || ft_strcmp(str, "##end") == 0)
			error("start/end before ants");
		else if (comments_or_commands(str, 1))
			continue;
		else
			break;
	}
	if(str == NULL)
		error("Error, empty map!!!");
	ft_putstr(str);
	all->number_of_ants = ft_atoi_ants(str);
	calc->number_of_ants = (int)all->number_of_ants;
}
