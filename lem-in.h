/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:03:29 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/30 16:20:04 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"

typedef	struct s_lem
{
	int number_of_ants;
}t_lem;

typedef struct s_rooms
{
	char *name;
	int data;
	int number_of_room;
	struct s_rooms *next;
	struct s_rooms *prev;
}t_rooms;

typedef	struct s_all
{
	unsigned number_of_ants;
	int numbers_of_rooms;
	t_rooms *first_room;
	t_rooms *last_room;



}t_all;

void	ft_parser(int argc, char **argv);
void 	ft_error(void);
void 	ft_isspace(char *str);
t_rooms	ft_create(t_rooms *rom);
void	all_rooms(t_all *all, int fd);
int		comments(char *str);

#endif
