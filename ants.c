/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:01:05 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/15 20:58:19 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

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

void	number_of_ants(t_all *all, int fd, t_calc *calc)
{
	char *str;

	str = NULL;
	if (get_next_line(fd, &str))
		ft_putstr(str);
	else
		error("Error, empty map!!!");
	all->number_of_ants = ft_atoi_ants(str);
	calc->number_of_ants = (int)all->number_of_ants;
}
