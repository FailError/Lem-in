/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/12/01 18:38:47 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_rooms	*ft_create(char **room) ///создаем комнату->обнуляем->записываем имя и координаты
{
	t_rooms *new;

	if(!(new = ft_memalloc(sizeof(t_rooms))))
		exit(-1);
	new->name = room[0];
	if (!ft_strncmp(new->name, "L", 1))
	{
		ft_printf("Error: not valid room name");
		exit(-1);
	}
	new->x = ft_atoi_ants(room[1]);
	new->y = ft_atoi_ants(room[2]);
	free(room);
	room = NULL;
	return (new);
}

//t_rooms *ft_push_back(t_rooms *head, char *str)
//{
//	t_rooms *ptr = head;
//	while(ptr->next != NULL)
//		ptr = ptr->next;
//	t_rooms *newnode = ft_create();
//	ptr->next = newnode;
//	newnode->next = NULL;
//	newnode->prev = ptr;
//	head->prev = newnode;
//
//	newnode->name = (char *) malloc(sizeof(char) * 5);
//	ft_strlcat(newnode->name, str, 5);
//	newnode->name[4] = '\0';
//	return (head);
//}

void	ft_error_str(char *str)
{
	ft_putstr(str);
	exit(-1);
}

int main(int argc, char **argv)
{
	int fd;
	t_all all;

	fd = open(argv[1], O_RDONLY);
	ft_bzero(&all, sizeof(t_all));
	number_of_ants(&all, fd);
	all_rooms(&all, fd);
	return (0);
}
