/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatprecnull2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 09:11:43 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				dlwidthfloat(long long int a)
{
	int res;

	res = 0;
	if (a == 0)
		res = 1;
	while (a != 0)
	{
		a /= 10;
		res++;
	}
	return (res);
}

int				ft_flminus(t_flags *all, long long int i, int count)
{
	if (all->fl1)
		all->sign ? ft_putchar1('-', all) : ft_putchar1('+', all);
	else
	{
		if (all->sign)
			ft_putchar1('-', all);
		else if (all->fl5)
			ft_putchar1(' ', all);
	}
	ft_putnbrfloat(i, all);
	all->fl4 ? ft_putchar1('.', all) : 0;
	while (all->width > count)
	{
		ft_putchar1(' ', all);
		count++;
	}
	return (0);
}

void			ft_putnbrfloat(long long int nb, t_flags *all)
{
	if (nb >= 10)
	{
		ft_putnbrfloat(nb / 10, all);
	}
	ft_putchar1(nb % 10 + 48, all);
}

int				ft_flplus(t_flags *all, long long int i, int count)
{
	if (all->fl3)
	{
		all->sign ? ft_putchar1('-', all) : 0;
		if (all->fl1 && !(all->sign))
			ft_putchar1('+', all);
		if (all->fl5 && !(all->sign))
			ft_putchar1(' ', all);
		while (all->width > count++)
			ft_putchar1('0', all);
		ft_putnbrfloat(i, all);
		all->fl4 ? ft_putchar1('.', all) : 0;
	}
	else
	{
		while (all->width > count++)
			ft_putchar1(' ', all);
		if (all->fl1 && !(all->sign))
			ft_putchar1('+', all);
		all->sign ? ft_putchar1('-', all) : 0;
		if (all->fl5 && !(all->sign))
			ft_putchar1(' ', all);
		ft_putnbrfloat(i, all);
		all->fl4 ? ft_putchar1('.', all) : 0;
	}
	return (0);
}
