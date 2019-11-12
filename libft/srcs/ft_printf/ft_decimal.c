/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:33:36 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_decimal(va_list args, t_flags *all)
{
	long int	x;
	int			y;
	int			z;

	x = 0;
	z = 0;
	ft_dinintialx(&x, all, args);
	ft_decimalhelp(&x, &y, all);
	all->precision > 0 && all->fl3 == '0' ? all->fl3 = '\0' : 1;
	all->fl2 == '-' ? all->fl3 = '\0' : 1;
	if (x >= 0)
	{
		all->precision <= y ? ft_preclessthanyx(z, y, x, all) : 0;
		all->precision > y ? ft_precmorethanyx(z, y, x, all) : 0;
	}
	else
	{
		all->precision <= y ? ft_xpreclessthany(z, y, x, all) : 0;
		all->precision > y ? ft_xprecmorethany(z, y, x, all) : 0;
	}
	return (0);
}

void			ft_preclessthanyx(int z, int y, long int x, t_flags *all)
{
	z = all->fl1 == '+' || all->fl5 == ' ' ? y + 1 : y;
	if (all->fl3 == '0' && (all->fl1 == '+') && !(all->t))
		ft_putchar1('+', all);
	else if (all->fl3 == '0' && (all->fl5 == ' '))
		ft_putchar1(' ', all);
	while (all->width > z && !(all->fl3))
	{
		ft_putchar1(' ', all);
		z++;
	}
	while (all->fl3 == '0' && all->width > z && all->precision <= y)
	{
		ft_putchar1('0', all);
		z++;
	}
	if (all->fl1 == '+' && !(all->fl3))
		ft_putchar1('+', all);
	else if (all->fl5 == ' ' && !(all->fl3))
		ft_putchar1(' ', all);
	x == 0 && all->t && all->precision == 0 ? 0 : ft_putnbrlong(x, all);
}

void			ft_precmorethanyx(int z, int y, long int x, t_flags *all)
{
	z = all->fl1 || all->fl5 ? y + (all->precision - y) + 1 :
	y + (all->precision - y);
	while (all->width > z)
	{
		ft_putchar1(' ', all);
		z++;
	}
	if (all->fl1 == '+')
		ft_putchar1('+', all);
	else if (all->fl5 == ' ')
		ft_putchar1(' ', all);
	while (all->precision > y)
	{
		ft_putchar1('0', all);
		y++;
	}
	ft_putnbrlong(x, all);
}

void			ft_xpreclessthany(int z, int y, long int x, t_flags *all)
{
	z = y + 1;
	all->fl3 ? ft_putchar1('-', all) : 1;
	while (all->width > y + 1 && !(all->fl3))
	{
		ft_putchar1(' ', all);
		y++;
	}
	while (all->width > y + 1 && all->fl3)
	{
		ft_putchar1('0', all);
		y++;
	}
	all->fl3 ? ft_putnbrplus(x, all) : ft_putnbrlong(x, all);
}

void			ft_xprecmorethany(int z, int y, long int x, t_flags *all)
{
	z = y + all->precision - y + 1;
	while (all->width > z)
	{
		ft_putchar1(' ', all);
		z++;
	}
	ft_putchar1('-', all);
	while (all->precision > y)
	{
		ft_putchar1('0', all);
		y++;
	}
	ft_putnbrplus(x, all);
}
