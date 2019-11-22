/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:05:49 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/22 15:56:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int main(int argc, char **argv)
{
	ft_parser(argc, argv);
}

void ft_parser(int argc, char **argv)
{
	char *str;
	int fd;

	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &str) == 1)
	{
		ft_printf("%s\n", str);
	}
}