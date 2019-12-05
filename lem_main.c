/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/12/05 21:41:29 by kbessa           ###   ########.fr       */
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

void	ft_error_str(char *str)
{
	ft_putstr(str);
	exit(-1);
}

int main(int argc, char **argv)
{
	int fd;
	t_all all;

	argc += 1;
	fd = open(argv[1], O_RDONLY);
	ft_bzero(&all, sizeof(t_all));
	number_of_ants(&all, fd);
	close(fd);
	return (0);
	all_rooms(&all, fd);
	return (0);
}
