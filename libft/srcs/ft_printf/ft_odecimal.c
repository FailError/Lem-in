/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_odecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:36:01 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int					ft_odecimal(va_list args, t_flags *all)
{
	unsigned long int	x;
	int					z;
	char				*v;

	x = 0;
	z = 0;
	ft_oinitialx(&x, all, args);
	v = ft_itoa_base16(x, 8, 1);
	x = ft_atoio(v);
	all->y = x == 0 ? 1 : dlwidtho(x);
	all->precision > 0 && all->fl3 == '0' ? all->fl3 = '\0' : 1;
	if (all->fl4 && all->width == 0 && !(all->t) && x == 0)
	{
		ft_putstr1(v, all);
		return (0);
	}
	if (all->precision <= all->y && all->t)
		ft_odecpreclessy(x, z, all);
	if (!(all->t))
		ft_odecnott(x, z, v, all);
	if (all->precision > all->y)
		ft_odecprecovery(x, z, all);
	x == 0 ? 0 : free(v);
	return (0);
}

unsigned long int	ft_atoio(const char *str)
{
	unsigned long int	res;
	int					minus;
	size_t				i;

	res = 0;
	minus = 1;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res >= 9223372036854775807 && minus == -1)
		return (0);
	else if (res > 9223372036854775807 && minus == 1)
		return (-1);
	return (res);
}

void				ft_odecpreclessy(unsigned long x, int z, t_flags *all)
{
	z = all->fl4 ? all->y + 1 : all->y;
	all->precision == 0 && x == 0 ? z = 1 : 0;
	all->precision == 1 && x == 0 ? z-- : 0;
	all->precision == 0 && x == 0 && all->t ? z = 1 : 0;
	!(all->fl4) && x == 0 && all->t ? z = 0 : 0;
	while ((all->width > z && (all->t || all->fl4)) || all->width > z)
	{
		ft_putchar1(' ', all);
		z++;
	}
	all->fl4 ? ft_putchar1('0', all) : 0;
	while (all->fl3 == '0' && all->width > z
		&& all->precision <= all->y)
	{
		ft_putchar1('0', all);
		z++;
	}
	x != 0 ? ft_putnbro(x, all) : 0;
}

void				ft_odecnott(unsigned long x, int z, char *v, t_flags *all)
{
	if (all->fl4 || all->fl3)
	{
		all->help = all->fl4 ? 1 : 0;
		all->fl3 && (all->width || all->precision) ? all->fl4 = '\0' : 1;
		all->width <= all->y ? all->fl4 = '#' : 0;
		z = all->fl4 && x != 0 ? all->y + 1 : all->y;
		while (!(all->fl4) && all->width > z++)
			ft_putchar1('0', all);
		while (all->fl4 && all->width > z++)
			ft_putchar1(' ', all);
		if (all->fl4 && !(all->fl3) && x != 0)
			ft_putchar1('0', all);
		else if (all->width == 0 && all->fl4)
			ft_putchar1('0', all);
		all->fl4 && !(all->t) && all->fl3 && all->help && x != 0 ?
		ft_putchar1('0', all) : 1;
		ft_putstr1(v, all);
	}
	else
	{
		while (all->width > all->y++)
			ft_putchar1(' ', all);
		ft_putstr1(v, all);
	}
}

void				ft_odecprecovery(unsigned long x, int z, t_flags *all)
{
	z = all->fl1 || all->fl5 ? all->y + (all->precision - all->y) + 1 :
	all->y + (all->precision - all->y);
	while (all->width > z)
	{
		ft_putchar1(' ', all);
		z++;
	}
	if (all->fl1 == '+')
		ft_putchar1('+', all);
	else if (all->fl5 == ' ')
		ft_putchar1(' ', all);
	while (all->precision > all->y)
	{
		ft_putchar1('0', all);
		all->y++;
	}
	ft_putnbro(x, all);
}
