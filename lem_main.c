/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/30 21:21:53 by kbessa           ###   ########.fr       */
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
			ants = ants * 10 + str[i] - '0';
			++i;
		}
		else
			ft_error();
	}
	i == 0 || i > 10 || ants > 2147483647 ? ft_error() : 0;
	free(str);
	return (ants);
}

int comments(char *str)
{
	if (str[0] == '#' && (str[1] != '#' || !str[1]))
	{
		free(str);
		return (1);
	}
	return (0);
}

void	number_of_ants(t_all *all, const int fd)
{
	char *str;

	str = NULL;
	get_next_line(fd, &str);
	ft_putstr(str);
	all->number_of_ants = ft_atoi_ants(str);
}

void	all_rooms(t_all *all, int fd)
{
	char	*str;

	str = NULL;
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		if (comments(str))
			continue;
	}
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
