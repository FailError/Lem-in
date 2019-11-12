/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 04:12:32 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_float(va_list args, t_flags *all)
{
	long double	xx;
	long double	n;
	char		*v;
	t_f			f;

	xx = 0;
	v = NULL;
	ft_finitialx(&f, all, &xx, args);
	if (all->t && all->precision == 0)
	{
		ft_precnull(all, (double)xx);
		return (0);
	}
	ft_fineedmorespace(&f, &n, &xx, all);
	if (!(v = (char *)malloc(sizeof(char) * f.len + 1)))
		return (0);
	ft_fcelayachast(&f, v, &xx);
	ft_formiruemmassiv(&f, &n, v);
	if (v[f.len - 1] != '9' && n >= 0.5)
		ft_fnotninelastnum(&f, all, v);
	else if (v[f.len - 1] == '9' && n >= 0.5)
		ft_fninelastnum(&f, all, v);
	else
		ft_fthreeother(all, v);
	return (0);
}

/*
**зануляем структуру и инициализируем xx
*/

void			ft_finitialx(t_f *f, t_flags *all, long double *xx,
va_list args)
{
	ft_bzero(f, sizeof(t_f));
	all->dlina == '\0' || all->dlina == 'l' ? *xx = va_arg(args, double) : 0;
	all->dlina == 'D' ? *xx = va_arg(args, long double) : 0;
}

/*
**узнаем знак сдвигом, получаем целую часть
**длина всего числа с точкой и мелочь...
*/

void			ft_fineedmorespace(t_f *f, long double *n, long double *xx,
t_flags *all)
{
	*n = *xx;
	*xx = ft_sign2nol2(*xx, all, f);
	all->sign ? *n = -*n : *n;
	f->x = (long long)*n;
	f->c = *xx ? 0 : 1;
	if (*n > 0 && *n < 1)
		f->x = 1;
	f->c = dlwidthfloat(f->x);
	f->x = (long long int)*n;
	*n -= f->x;
	f->len = f->c + 1 + f->accur;
}

long double		ft_sign2nol2(double t, t_flags *all, t_f *f)
{
	int				sign;
	unsigned long	*ptr;

	ptr = (unsigned long *)&t;
	sign = *ptr >> 63;
	all->sign = sign;
	all->counter = all->sign ? 1 : 0;
	if (t == -0 || t == 0)
		t = 0;
	else
		t = t < 0 ? -t : t;
	f->accur = all->t ? all->precision : 6;
	return (t);
}

/*
**точка в целой части, ставим 0 в конец
**длина целой части с точкой...
*/

void			ft_fcelayachast(t_f *f, char *v, const long double *xx)
{
	v[f->c] = '.';
	v[f->len] = '\0';
	f->c1 = f->c + 1;
	if (*xx == 0)
		v[--f->c] = 0 + '0';
}
