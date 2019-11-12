/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 23:01:14 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_point(va_list args, t_flags *all)
{
	long long		x;
	unsigned int	i;
	char			*f;

	x = (long long)va_arg(args, void *);
	f = ft_itoa_base(x, 16);
	i = ft_strlen(f) + 2;
	if (all->fl2)
		ft_pwithfl2(f, i, all);
	else
		ft_pwithoutfl2(f, i, x, all);
	x == 0 ? 0 : free(f);
	return (0);
}

char	*ft_itoa_base(long long int value, int base)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;

	tab_base = "0123456789abcdef";
	if (value == 0)
		return ("0");
	taille = digit_count(value, base);
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (NULL);
	i = 1;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	return (ret);
}

size_t	digit_count(unsigned long nb, int base)
{
	size_t	i;

	i = 0;
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}

void	ft_pwithfl2(char *f, unsigned int i, t_flags *all)
{
	ft_putstr1("0x", all);
	ft_putstr1(f, all);
	while (all->width > (int)i)
	{
		ft_putchar1(' ', all);
		i++;
	}
}

void	ft_pwithoutfl2(char *f, unsigned int i, long long x, t_flags *all)
{
	while (all->width > (int)i)
	{
		ft_putchar1(' ', all);
		i++;
	}
	ft_putstr1("0x", all);
	while (all->t && all->precision > (int)i - 2)
	{
		ft_putchar1('0', all);
		i++;
	}
	x == 0 && all->t && all->precision == 0 ? 0 : ft_putstr1(f, all);
}
