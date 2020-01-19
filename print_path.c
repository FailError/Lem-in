/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:05:03 by bgilwood          #+#    #+#             */
/*   Updated: 2020/01/18 21:06:58 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ways			**final_map_to_arr(t_ways *ways, t_calc *calc)
{
	int			i;
	t_ways		*way;
	t_ways		**arr;

	arr = (t_ways **)ft_memalloc(sizeof(t_ways *) * (calc->number_of_ways + 1));
	way = ways;
	i = 0;
	while (way)
	{
		arr[i] = way;
		way = way->next;
		i++;
	}
	return (arr);
}

void			expression(t_ways **arr_p)
{
	int			i;
	int			j;
	int			current_l;
	int			prev_l;

	j = 1;
	while (arr_p[j])
	{
		i = 0;
		current_l = 0;
		prev_l = 0;
		while (i != j)
		{
			prev_l += arr_p[i]->length - 1;
			current_l += arr_p[j]->length - 1;
			i++;
		}
		arr_p[j]->expression = current_l - prev_l;
		j++;
	}
}

void			print_path(t_all *all, t_ways *ways, t_calc *calc)
{
	int			ants_ostatok;
	int			ants_current;
	t_ways		**arr_paths;
	int			i;

	i = 0;
	ants_ostatok = (int)all->number_of_ants;
	ants_current = 1;
	arr_paths = final_map_to_arr(ways, calc);
	expression(arr_paths);
	while (all->last_room->itogo != all->number_of_ants)
	{
		while (arr_paths[i])
		{
			walking_ants(arr_paths[i], &ants_ostatok, &ants_current);
			i++;
		}
		ft_printf("\n");
		calc->str_sum++;
		i = 0;
	}
	free(arr_paths);
}
