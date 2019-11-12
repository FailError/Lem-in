/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xhexmin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 08:18:16 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_xhexmin(va_list args, t_flags *all)
{
	unsigned long int	x;
	int					i;
	char				*s;

	x = 0;
	ft_xxinitialx(&x, all, args);
	s = ft_itoa_base16(x, 16, 1);
	i = ft_strlen(s);
	all->j = x == 0 ? 0 : i;
	if (all->fl4 && x != 0)
	{
		ft_putstr1("0x", all);
		all->j += 2;
	}
	if (all->t)
		ft_xminwitht(x, i, s, all);
	else if (!(all->t))
		ft_xminnot(x, s, all);
	else if (!(all->t && all->width))
		ft_putstr1(s, all);
	x == 0 ? 0 : free(s);
	return (0);
}

void	ft_xminwitht(unsigned long x, int i, char *s, t_flags *all)
{
	while (all->precision > i)
	{
		ft_putchar1('0', all);
		i++;
		all->j++;
	}
	x == 0 && all->precision == 0 ? 0 : ft_putstr1(s, all);
	x == 0 && all->precision > 0 ? all->j += 1 : 0;
	while (all->width > all->j)
	{
		ft_putchar1(' ', all);
		all->j++;
	}
}

void	ft_xminnot(unsigned long x, char *s, t_flags *all)
{
	x == 0 ? all->j += 1 : 0;
	ft_putstr1(s, all);
	while (all->width > all->j)
	{
		ft_putchar1(' ', all);
		all->j++;
	}
}

void	ft_xxminnot(unsigned long x, char *s, t_flags *all)
{
	x == 0 ? all->j += 1 : 0;
	ft_putstr1(s, all);
	while (all->width > all->j)
	{
		ft_putchar1(' ', all);
		all->j++;
	}
}
