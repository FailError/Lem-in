/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:03:29 by kbessa            #+#    #+#             */
/*   Updated: 2019/12/02 14:47:52 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"

typedef struct		s_rooms
{
	unsigned		x;
	unsigned		y;
	t_list			*links;
	char			*name;
	int				data;
	int				number_of_room;
	struct s_rooms	*next;
	struct s_rooms	*prev;
}					t_rooms;

typedef	struct		s_all
{
	unsigned		number_of_ants;
	int				numbers_of_rooms;
	t_rooms			*first_room;
	t_rooms			*last_room;
	t_list			*list_of_rooms;
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
t_list				*ft_lstnew_ptr(void const *content);
void				if_room_coord(t_all *all, char *str);

#endif
