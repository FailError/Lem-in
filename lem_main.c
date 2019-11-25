/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/25 21:13:17 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int main(int argc, char **argv)
{
	ft_parser(argc, argv);
}

t_rooms	*ft_create(void)
{
	t_rooms *rom = (t_rooms *)malloc(sizeof(t_rooms));
	rom->name = NULL;
	rom->data = 0;
	rom->next = NULL;
	rom->prev = rom;
	return (rom);
}

t_rooms *ft_push_back(t_rooms *rooms, char *str)
{
	t_rooms *ptr = rooms;
	while(ptr->next != NULL)
		ptr = ptr->next;
	t_rooms *newnode = ft_create();//(t_rooms *)malloc(sizeof(t_rooms));
	ptr->next = newnode;
	newnode->next = NULL;
	newnode->prev = ptr;

	newnode->name = (char *) malloc(sizeof(char) * 5);
	ft_strlcat(newnode->name, str, 5);
	return (rooms);
}

void ft_parser(int argc, char **argv)
{
	char *str = NULL;
	int fd;
	t_rooms *rooms = ft_create();
	//t_rooms *head = rooms;
	int i = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &str) == 1)
	{
		while (str[4] && str[4] == ' ')
		{
			ft_push_back(rooms, str);




//			t_rooms *rooms1 = (t_rooms *)malloc(sizeof(t_rooms));
//			rooms1->name = (char *) malloc(sizeof(char) * 5);
//			ft_strlcat(rooms1->name, str, 5);
//			rooms->next = NULL;
		}
	}
	if (ft_strcmp(str, "##start") == 0)
		i = 1;
}