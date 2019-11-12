/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:28:36 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_decimalmin(va_list args, t_flags *all)
{
	long int	x;
	int			y;
	int			z;

	x = 0;
	z = 0;
	ft_dinintialx(&x, all, args);
	y = dlwidth(x);
	z = all->fl1 == '+' || all->fl5 == ' ' ? y + 1 : y;
	if (x >= 0)
	{
		all->precision > y ? ft_dminprecmorethanyx(y, x, all) : 0;
		y = dlwidth(x);
		x == 0 && !(all->t) && all->width ? z += 1 : 0;
		all->precision <= y ? ft_dminpreclessthanyx(z, x, all) : 0;
	}
	else
	{
		all->precision > y ? ft_xdminprecmorethany(y, x, all) : 0;
		y = dlwidth(x);
		all->precision <= y ? ft_xdminpreclessthany(y, x, all) : 0;
	}
	return (0);
}

void			ft_dminprecmorethanyx(int y, long int x, t_flags *all)
{
	if (all->fl1)
		ft_putchar1('+', all);
	else if (all->fl5)
		ft_putchar1(' ', all);
	while (all->precision > y)
	{
		write(1, "0", 1);
		y++;
		all->re += 1;
	}
	x != 0 ? ft_putnbrlong(x, all) : 0;
	y += (all->fl1 || all->fl5) ? 1 : 0;
	while (all->width > y)
	{
		write(1, " ", 1);
		y++;
		all->re += 1;
	}
}

void			ft_dminpreclessthanyx(int z, long int x, t_flags *all)
{
	if (all->fl1)
		ft_putchar1('+', all);
	else if (all->fl5)
		ft_putchar1(' ', all);
	x != 0 ? ft_putnbrlong(x, all) : 0;
	x == 0 && !(all->t) ? ft_putnbrlong(x, all) : 0;
	while (all->width > z)
	{
		write(1, " ", 1);
		z++;
		all->re += 1;
	}
}

void			ft_xdminprecmorethany(int y, long int x, t_flags *all)
{
	ft_putchar1('-', all);
	while (all->precision > y)
	{
		ft_putchar1('0', all);
		y++;
	}
	ft_putnbrplus(x, all);
	while (all->width > y + 1)
	{
		ft_putchar1(' ', all);
		y++;
	}
}

void			ft_xdminpreclessthany(int y, long int x, t_flags *all)
{
	ft_putchar1('-', all);
	ft_putnbrplus(x, all);
	while (all->width > y + 1)
	{
		ft_putchar1(' ', all);
		y++;
	}
}
