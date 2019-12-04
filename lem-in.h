/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:03:29 by kbessa            #+#    #+#             */
/*   Updated: 2019/12/04 21:14:36 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"

typedef struct		s_rooms
{
	unsigned		x; ///координаты
	unsigned		y;
	t_list			*links; ///список связных комнат
	char			*name; ///имя комнаты
	unsigned		num; ///номер комнаты
}					t_rooms;

typedef	struct		s_all
{
	t_rooms			**arr_rooms; ///массив указателей на комнаты из списка
	unsigned		number_of_ants;
	int				number_of_all_rooms; ///общее кол-во комнат
	t_rooms			*first_room; ///указатель на 1-ую комнату
	t_rooms			*last_room; ///указатель на последнюю комнату
	t_list			*list_of_rooms; ///список комнат
}					t_all;

void				ft_error(void);
t_rooms				*ft_create(char **room);
void				all_rooms(t_all *all, int fd);
int					ifcomments(char *str);
unsigned			ft_atoi_ants(char *str);
int					start_end(t_all *all, int fd, char *str);
void				ft_error_str(char *str);
void				number_of_ants(t_all *all, int fd);
void				check_name_coord(char **room);
void				check_name_coord2(char **room);
t_list				*ft_lstnew_ptr(void const *content);
void				room_coord(t_all *all, char *str);
void				struct_to_array(t_all *all);
void				links_in_array(t_all *all, char *str);
t_list				*next(t_list *tmp);
void				double_name(t_all *all);
void 				qs2(t_all *all, int first, int last);
t_rooms				*binary_search(char *tmp, int all_rooms, t_rooms **rooms);

#endif
