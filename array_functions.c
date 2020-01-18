/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:42:22 by bgilwood          #+#    #+#             */
/*   Updated: 2020/01/18 22:17:00 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				qs_swap(t_rooms **arr_rooms, t_rooms *tmp,
					int *left, int *right)
{
	tmp = arr_rooms[*left];
	arr_rooms[*left] = arr_rooms[*right];
	arr_rooms[*right] = tmp;
	*left += 1;
	*right -= 1;
}

void				quick_sort(t_rooms **arr_rooms, int first, int last)
{
	t_rooms			*tmp;
	int				left;
	int				right;
	char			*middle;

	tmp = NULL;
	if (first < last)
	{
		left = first;
		right = last;
		middle = arr_rooms[(left + right) / 2]->name;
		while (left <= right)
		{
			while ((ft_strcmp(arr_rooms[left]->name, middle) < 0))
				left++;
			while ((ft_strcmp(arr_rooms[right]->name, middle) > 0))
				right--;
			if (left <= right)
				qs_swap(arr_rooms, tmp, &left, &right);
		}
		quick_sort(arr_rooms, first, right);
		quick_sort(arr_rooms, left, last);
	}
}

void				struct_to_array(t_all *all)
{
	unsigned		i;

	!all->first_room || !all->last_room ? error("no start/finish") : 0;
	all->ar_room = ft_memalloc(sizeof(t_rooms *) * all->n_rooms);
	i = 0;
	while (all->list_of_rooms)
	{
		all->ar_room[i] = all->list_of_rooms->content;
		all->list_of_rooms = next(all->list_of_rooms);
		i++;
	}
	all->list_of_rooms = NULL;
	double_name(all);
	quick_sort(all->ar_room, 0, (int)all->n_rooms - 1);
}

t_rooms				*binary_search(char *current, unsigned all_rooms,
					t_rooms **rooms)
{
	int				low;
	int				high;
	int				mid;
	char			*guess;

	low = 0;
	high = (int)all_rooms - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		guess = rooms[mid]->name;
		if (!ft_strcmp(guess, current))
			return (rooms[mid]);
		if (ft_strcmp(guess, current) > 0)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return (NULL);
}

void				free_str_double_star(char **str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
}
