/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xhex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 00:47:35 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_xhex(va_list args, t_flags *all)
{
	unsigned long int	x;
	int					i;
	char				*s;

	x = 0;
	ft_xxinitialx(&x, all, args);
	s = ft_itoa_base16(x, 16, 1);
	i = ft_strlen(s);
	all->j = i;
	if (all->t && all->fl4)
		i = all->precision > i ? all->precision + 2 : i + 2;
	if (all->t && !(all->fl4))
		i = all->precision > i ? all->precision : i;
	if (all->t)
		ft_xwitht(x, i, s, all);
	else if (!(all->t) && all->width > 0)
		ft_xnotwidth(x, i, s, all);
	else if (!(all->t && all->width))
	{
		all->fl4 && x != 0 ? ft_putstr1("0x", all) : 1;
		ft_putstr1(s, all);
	}
	x == 0 ? 0 : free(s);
	return (0);
}

void	ft_xxinitialx(unsigned long *x, t_flags *all, va_list args)
{
	all->dlina == '\0' ? *x = va_arg(args, unsigned int) : 0;
	all->dlina == 'h' ? *x = (unsigned short)va_arg(args, int) : 0;
	all->dlina == 'H' ? *x = (unsigned char)va_arg(args, int) : 0;
	all->dlina == 'l' ? *x = va_arg(args, unsigned long int) : 0;
	all->dlina == 'L' ? *x = va_arg(args, unsigned long int) : 0;
}

void	ft_xwitht(unsigned long x, int i, char *s, t_flags *all)
{
	x == 0 ? i -= 2 : 1;
	x == 0 && all->t && all->precision == 0 ? i = 0 : 0;
	x == 0 && all->t && all->precision > 0 ? i = all->precision : 0;
	while (all->width > i)
	{
		ft_putchar1(' ', all);
		i++;
	}
	all->fl4 && x != 0 ? ft_putstr1("0x", all) : 1;
	while (all->precision > all->j)
	{
		ft_putchar1('0', all);
		all->j++;
	}
	x == 0 && all->t && all->precision == 0 ? 0 : ft_putstr1(s, all);
}

void	ft_xnotwidth(unsigned long x, int i, char *s, t_flags *all)
{
	all->fl4 ? i += 2 : 1;
	x == 0 && (all->fl3 || all->fl4) ? i -= 2 : 1;
	while (!(all->fl3) && all->width > i)
	{
		ft_putchar1(' ', all);
		i++;
	}
	all->fl4 && x != 0 ? ft_putstr1("0x", all) : 1;
	while (all->fl3 && all->fl4 && all->width > i)
	{
		ft_putchar1('0', all);
		i++;
	}
	while (all->fl3 && !(all->fl4) && all->width > all->j)
	{
		ft_putchar1('0', all);
		all->j++;
	}
	ft_putstr1(s, all);
}
