/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/28 17:58:06 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_rooms	ft_create()
{
	t_rooms rom = *(t_rooms *)malloc(sizeof(t_rooms));
	rom.name = NULL;
	rom.data = 0;
	rom.number_of_room = 1;
	rom.next = NULL;
	//rom.prev = rom;
	return (rom);
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

void	number_of_ants(t_all *all, const int fd)
{
	char *str;

	str = NULL;
	get_next_line(fd, &str);
	all->number_of_ants = ft_atoi(str);
	free(str);
}

void	ft_isspace(char *str)
{
	if(*str == ' ' || *str == '\t' || *str == '\r' || *str == '\v' || *str == '\f')
		ft_isspace(str);
}

void ft_parser(int argc, char **argv)
{
	int fd;
	t_all all;
	//t_lem *lemin = (t_lem *)malloc(sizeof(t_lem));

	fd = open(argv[1], O_RDONLY);
	ft_bzero(&all, sizeof(t_all));
	number_of_ants(&all, fd);
	//all = ft_create(&all);



	if(fd < 0)
		fd = 0;

//	while (get_next_line(fd, &str) == 1)
//	{
//		ft_putstr(str);
//		ft_isspace(str);
//		if (ft_strcmp(str, "##start") == 0)
//			i = 1;
//	}
}

int main(int argc, char **argv)
{
	ft_parser(argc, argv);
}
