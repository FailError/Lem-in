/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 06:57:40 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_nullspecplus(t_flags *all)
{
	if (all->fl3)
	{
		while (all->width-- > 1)
			ft_putchar1('0', all);
		ft_putchar1('%', all);
	}
	else
	{
		while (all->width-- > 1)
			ft_putchar1(' ', all);
		ft_putchar1('%', all);
	}
}

int		ft_putchar1(char c, t_flags *all)
{
	write(1, &c, 1);
	all->re += 1;
	return (0);
}

void	ft_putstr1(const char *str, t_flags *all)
{
	int i;

	i = 0;
	if (str)
	{
		i = ft_strlen(str);
		write(1, str, i);
		all->re += i;
	}
}
