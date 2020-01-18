/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:03:29 by kbessa            #+#    #+#             */
/*   Updated: 2020/01/18 21:10:54 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct		s_rooms
{
	unsigned		x;
	unsigned		y;
	t_list			*links;
	char			*name;
	int				lvl;
	int				ant_n;
	int				itogo;
	int 			wputi;
}					t_rooms;

typedef	struct		s_all
{
	int 			end;
	int				success;
	unsigned		number_of_ants;
	unsigned		num_all_rooms;
	t_list			*list_of_rooms;
	t_rooms			**ar_room;
	t_rooms			*first_room;
	t_rooms			*last_room;
	t_rooms			**que;
}					t_all;

typedef	struct		s_way
{
	int				steps;
	t_list			*way_t;
	int				expression;
	int				length;
	t_rooms			**in_array;
	struct s_way	*next;
}					t_ways;

typedef struct		s_sum
{
	int				number_of_ants;
	int				sum_steps_all_ways;
	int				number_of_ways;
	int				result;
}					t_calc;

t_rooms				*ft_create(char **room);
void				all_rooms(t_all *all, int fd);
int					comments_or_commands(char *str, int c);
unsigned			ft_atoi_ants(char *str);
int					start_end(t_all *all, int fd, char *str);
void				number_of_ants(t_all *all, int fd, t_calc *calc);
void				check_name_coord(char **room);
void				check_name_coord2(char **room);
t_list				*ft_lstnew2(void const *content);
void				room_coord(t_all *all, char *str);
void				struct_to_array(t_all *all);
void				links_add(t_all *all, char *str);
t_list				*next(t_list *tmp);
void				double_name(t_all *all);
void				quick_sort(t_rooms **arr_rooms, int first, int last);
t_rooms				*binary_search(char *current, unsigned all_rooms,
					t_rooms **rooms);
void				free_str_double_star(char **str);
int					bfs(t_all *all);
t_ways				*reverse_path(t_rooms *last, t_rooms *first);
void				zero_lvl_que(t_all *all);
void				push_v_konec(t_ways **list_ways, t_ways *new);
void				mark_path(t_ways *new);
int					check_double_room_in_list(t_list *links, t_rooms *room);
void				in_array(t_ways *new);
int					serch_edge(t_ways *ways, t_ways *new, t_calc *calc, t_rooms *first);
void				calculated(t_calc *calc, t_ways *ways);
int					new_calc(t_calc *calc, t_ways *new);
void				print_path(t_all *all, t_ways *ways, t_calc *calc);
void				doubleminus(const char *str);
void				walking_ants(t_ways *ways, int *ants_ostatok, int *ants_current);

#endif
