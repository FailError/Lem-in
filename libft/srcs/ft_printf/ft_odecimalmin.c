/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_odecimalmin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:44:26 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int					ft_odecimalmin(va_list args, t_flags *all)
{
	unsigned long int	x;
	int					y;
	int					z;
	char				*v;

	x = 0;
	ft_oinitialx(&x, all, args);
	v = ft_itoa_base16(x, 8, 1);
	x = ft_atoio(v);
	y = dlwidtho(x);
	z = all->fl4 ? y + 1 : y;
	all->precision == 0 && x == 0 ? z = 0 : 0;
	if (all->precision > y)
		ft_odecminprecovery(x, y, all);
	y = dlwidtho(x);
	if (all->precision <= y)
		ft_odecminpreclessy(x, z, all);
	x == 0 ? 0 : free(v);
	return (0);
}

void				ft_oinitialx(unsigned long *x, t_flags *all, va_list args)
{
	all->dlina == '\0' ? *x = va_arg(args, unsigned int) : 0;
	all->dlina == 'h' ? *x = (unsigned short)va_arg(args, int) : 0;
	all->dlina == 'H' ? *x = (unsigned char)va_arg(args, int) : 0;
	all->dlina == 'l' ? *x = va_arg(args, unsigned long int) : 0;
	all->dlina == 'L' ? *x = va_arg(args, unsigned long int) : 0;
}

void				ft_odecminprecovery(unsigned int x, int y, t_flags *all)
{
	while (all->precision > y)
	{
		ft_putchar1('0', all);
		y++;
	}
	ft_putnbro(x, all);
	y += (all->fl1 || all->fl5) ? 1 : 0;
	while (all->width > y)
	{
		ft_putchar1(' ', all);
		y++;
	}
}

void				ft_odecminpreclessy(unsigned int x, int z, t_flags *all)
{
	all->fl4 && all->t ? ft_putchar1('0', all) : 1;
	all->fl4 && x != 0 && all->precision > z ? ft_putchar1('0', all) : 1;
	all->fl4 && !(all->t) && x > 0 ? ft_putchar1('0', all) : 1;
	x != 0 ? ft_putnbro(x, all) : 0;
	x == 0 && !(all->t) ? ft_putnbro(x, all) : 0;
	x == 0 && all->precision == 0 ? z++ : 0;
	x == 0 && all->precision == 1 ? z-- : 0;
	all->precision == 0 && x == 0 && all->t ? z = 1 : 0;
	!(all->fl4) && x == 0 && all->t ? z = 0 : 0;
	while (all->width > z++)
		ft_putchar1(' ', all);
}

void				ft_putnbro(unsigned long int nb, t_flags *all)
{
	unsigned long int n;

	n = nb;
	if (n >= 10)
	{
		ft_putnbro(n / 10, all);
	}
	ft_putchar1(n % 10 + 48, all);
}
