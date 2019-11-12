/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:29:43 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_dinintialx(long int *x, t_flags *all, va_list args)
{
	all->dlina == '\0' ? *x = va_arg(args, int) : 0;
	all->dlina == 'h' ? *x = (short)va_arg(args, int) : 0;
	all->dlina == 'H' ? *x = (char)va_arg(args, int) : 0;
	all->dlina == 'l' ? *x = va_arg(args, long int) : 0;
	all->dlina == 'L' ? *x = va_arg(args, long int) : 0;
}

void			ft_decimalhelp(const long int *x, int *y, t_flags *all)
{
	all->t ? all->fl3 = '\0' : 0;
	if (*x == 0 && all->precision > 0)
		*y = 1;
	else if (*x == 0 && all->t && all->precision == 0)
		*y = 0;
	else if (*x == 0 && !(all->t) && all->width)
		*y = 1;
	else
		*y = dlwidth(*x);
}

void			ft_putnbrplus(long nb, t_flags *all)
{
	long int n;

	n = (nb < 0) ? -nb : nb;
	if (n >= 10)
	{
		ft_putnbrplus(n / 10, all);
	}
	ft_putchar1(n % 10 + 48, all);
}

void			ft_putnbrlong(long int nb, t_flags *all)
{
	unsigned long int n;

	if (nb < 0)
	{
		ft_putchar1('-', all);
		n = -1 * nb;
	}
	else
		n = nb;
	if (n >= 10)
	{
		ft_putnbrlong(n / 10, all);
	}
	ft_putchar1(n % 10 + 48, all);
}
