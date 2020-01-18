/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:00:45 by bgilwood          #+#    #+#             */
/*   Updated: 2020/01/18 21:05:42 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			for_len_2(t_ways *arr, int *ants_ostatok, int *ants_current)
{
	ft_printf("L%d-%s ", *ants_current, arr->in_array[1]->name);
	arr->in_array[1]->itogo++;
	*ants_ostatok -= 1;
	*ants_current += 1;
}

void			going_to_last_room(t_ways *arr)
{
	ft_printf("L%d-%s ", arr->in_array[arr->length - 2]->ant_n,
		arr->in_array[arr->length - 1]->name);
	arr->in_array[arr->length - 1]->itogo++;
	arr->in_array[arr->length - 2]->ant_n = 0;
}

void			going_to_next_room(t_ways *arr, int last)
{
	arr->in_array[last + 1]->ant_n = arr->in_array[last]->ant_n;
	ft_printf("L%d-%s ", arr->in_array[last]->ant_n,
		arr->in_array[last + 1]->name);
	arr->in_array[last]->ant_n = 0;
}

void			walking_ants(t_ways *ways, int *ants_ostatok, int *ants_current)
{
	int last;

	if (ways->length == 2 && *ants_ostatok > ways->expression)
		for_len_2(ways, ants_ostatok, ants_current);
	else
	{
		if (ways->in_array[ways->length - 2]->ant_n)
			going_to_last_room(ways);
		last = ways->length - 3;
		while (last != 0)
		{
			if (ways->in_array[last]->ant_n)
				going_to_next_room(ways, last);
			last--;
		}
		if (*ants_ostatok > ways->expression)
		{
			ways->in_array[1]->ant_n = *ants_current;
			ft_printf("L%d-%s ", *ants_current, ways->in_array[1]->name);
			*ants_ostatok -= 1;
			*ants_current += 1;
		}
	}
}
