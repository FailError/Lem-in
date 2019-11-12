/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 09:06:36 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**запись целой части, если она > 0 и == 0
**запись дробной части
*/

void			ft_formiruemmassiv(t_f *f, long double *n, char *v)
{
	long long null;

	null = f->x;
	while (f->x)
	{
		v[--f->c] = f->x % 10 + '0';
		f->x /= 10;
	}
	if (*n > 0 && *n < 1 && null == 0)
	{
		v[--f->c] = 0 + '0';
		f->c++;
	}
	while (f->i < f->accur)
	{
		*n *= 10;
		f->x = (long long)*n;
		v[f->c1 + f->i] = f->x + '0';
		*n -= f->x;
		f->i++;
	}
}

/*
**ласт число в массиве != 9
**и след число >= 5
*/

void			ft_fnotninelastnum(t_f *f, t_flags *all, char *v)
{
	v[f->len - 1] += 1;
	config2(all, v);
	if (all->fl2 == '\0')
		ft_flplus2(all, v);
	else
		ft_flminus2(all, v);
	free(v);
}

t_flags			*config2(t_flags *all, char *v)
{
	if (all->fl2 && all->fl3)
		all->fl3 = '\0';
	if (all->fl1 && all->fl5)
		all->fl5 = '\0';
	if (all->fl1 && all->sign == 0)
		all->counter += 1;
	if (all->fl5 && all->sign == 0)
		all->counter += 1;
	all->counter += ft_strlen(v);
	return (all);
}

int				ft_flplus2(t_flags *all, char *v)
{
	if (all->fl3)
	{
		if (all->sign)
			ft_putchar1('-', all);
		if (all->fl1 && !(all->sign))
			ft_putchar1('+', all);
		if (all->fl5 && !(all->sign))
			ft_putchar1(' ', all);
		while (all->width > all->counter++)
			ft_putchar1('0', all);
		ft_putstr1(v, all);
	}
	else
	{
		while (all->width > all->counter++)
			ft_putchar1(' ', all);
		if (all->fl1 && !(all->sign))
			ft_putchar1('+', all);
		if (all->sign)
			ft_putchar1('-', all);
		if (all->fl5 && !(all->sign))
			ft_putchar1(' ', all);
		ft_putstr1(v, all);
	}
	return (0);
}

int				ft_flminus2(t_flags *all, char *v)
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
	ft_putstr1(v, all);
	while (all->width > all->counter++)
		ft_putchar1(' ', all);
	return (0);
}
