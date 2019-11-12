/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_udecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 22:18:40 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_udecimal(va_list args, t_flags *all)
{
	unsigned long int	x;
	int					y;
	int					z;

	x = 0;
	z = 0;
	ft_uinitialx(&x, all, args);
	y = x == 0 ? 1 : dlwidthu(x);
	x == 0 && all->precision == 0 ? y = 0 : 0;
	x == 0 && !(all->t) ? y = 1 : 0;
	all->precision > 0 && all->fl3 == '0' ? all->fl3 = '\0' : 1;
	all->fl2 == '-' ? all->fl3 = '\0' : 1;
	if (all->precision <= y)
		ft_udecpreclessy(x, y, z, all);
	if (all->precision > y)
		ft_udecprecovery(x, y, z, all);
	return (0);
}

void	ft_uinitialx(unsigned long *x, t_flags *all, va_list args)
{
	all->dlina == '\0' ? *x = va_arg(args, unsigned int) : 0;
	all->dlina == 'h' ? *x = (unsigned short)va_arg(args, int) : 0;
	all->dlina == 'H' ? *x = (unsigned char)va_arg(args, int) : 0;
	all->dlina == 'l' ? *x = va_arg(args, unsigned long int) : 0;
	all->dlina == 'L' ? *x = va_arg(args, unsigned long int) : 0;
}

void	ft_udecpreclessy(unsigned long x, int y, int z, t_flags *all)
{
	z = all->fl1 == '+' || all->fl5 == ' ' ? y + 1 : y;
	if (all->fl3 == '0' && (all->fl1 == '+'))
		ft_putchar1('+', all);
	else if (all->fl3 == '0' && (all->fl2 == ' '))
		ft_putchar1(' ', all);
	while (!(all->fl3) && all->width > z++)
		ft_putchar1(' ', all);
	while (all->precision <= y && all->fl3 == '0' && all->width > z++)
		ft_putchar1('0', all);
	if (x == 0 && (all->precision == 0))
		x = 0;
	else if (x == 0 && (all->precision == 1))
		ft_putchar1('0', all);
	else
		ft_putnbru(x, all);
	x == 0 && !(all->t) ? ft_putchar1('0', all) : 0;
}

void	ft_udecprecovery(unsigned long x, int y, int z, t_flags *all)
{
	z = all->fl1 || all->fl5 ? y + (all->precision - y) + 1 :
	y + (all->precision - y);
	while (all->width > z++)
		ft_putchar1(' ', all);
	if (all->fl1 == '+')
		ft_putchar1('+', all);
	else if (all->fl5 == ' ')
		ft_putchar1(' ', all);
	while (all->precision > y++)
		ft_putchar1('0', all);
	ft_putnbru(x, all);
}
