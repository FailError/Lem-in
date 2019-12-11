/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/12/11 22:31:49 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_rooms	*ft_create(char **room) ///создаем комнату->обнуляем->записываем имя и координаты
{
	t_rooms *new;

	if(!(new = ft_memalloc(sizeof(t_rooms))))
		ft_error_str("\x1B[31mMemory allocation error\033[0m");
	new->name = room[0];
	if (new->name[0] == 'L')
		ft_error_str("\x1B[31mError, name cannot begin with 'L'\033[0m");
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

	argc = 0;
	if(argv[1])
		fd = open(argv[1], O_RDONLY);
	else
		exit(0);
	ft_bzero(&all, sizeof(t_all));
	number_of_ants(&all, fd);
	all_rooms(&all, fd);
//	bfs(&all);
	close(fd);
	return (0);
}
