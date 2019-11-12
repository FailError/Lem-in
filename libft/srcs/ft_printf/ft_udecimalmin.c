/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_udecimalmin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 08:08:31 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_udecimalmin(va_list args, t_flags *all)
{
	unsigned long int	x;
	int					y;
	int					z;

	x = 0;
	ft_uinitialx(&x, all, args);
	y = dlwidthu(x);
	z = all->fl1 == '+' || all->fl5 == ' ' ? y + 1 : y;
	if (all->fl1)
		ft_putchar1('+', all);
	else if (all->fl5)
		ft_putchar1(' ', all);
	if (all->precision > y)
		ft_udecminprecovery(x, y, all);
	y = dlwidthu(x);
	x == 0 && !(all->t) ? z += 1 : 0;
	if (all->precision <= y)
		ft_udecminpreclessy(x, z, all);
	return (0);
}

void	ft_udecminprecovery(unsigned int x, int y, t_flags *all)
{
	while (all->precision > y)
	{
		ft_putchar1('0', all);
		y++;
	}
	x == 0 && (all->precision == 0 || all->precision >= 1) ? 0 :
	ft_putnbru(x, all);
	y += (all->fl1 || all->fl5) ? 1 : 0;
	while (all->width > y)
	{
		ft_putchar1(' ', all);
		y++;
	}
}

void	ft_udecminpreclessy(unsigned long int x, int z, t_flags *all)
{
	x == 0 && (all->precision == 0 || all->precision == 1) ? 0 :
	ft_putnbru(x, all);
	x == 0 && !(all->t) ? ft_putchar1('0', all) : 0;
	while (all->width > z)
	{
		ft_putchar1(' ', all);
		z++;
	}
}

void	ft_putnbru(unsigned long int nb, t_flags *all)
{
	unsigned long int	n;

	n = nb;
	if (n >= 10)
	{
		ft_putnbru(n / 10, all);
	}
	ft_putchar1(n % 10 + 48, all);
}
