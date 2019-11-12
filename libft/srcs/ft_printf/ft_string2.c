/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 08:41:41 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_strplus(va_list args, t_flags *all)
{
	void	*s;
	char	*d;
	int		i;

	d = NULL;
	s = NULL;
	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	i = ft_strlen(s);
	if (!(d = all->t ? (char *)malloc(sizeof(char) * all->precision + 1) :
		(char *)malloc(sizeof(char) * i + 1)))
		return (0);
	if (all->t)
	{
		d[all->precision] = '\0';
		ft_strpluswitht(s, d, i, all);
	}
	else if (!(all->t))
	{
		d[i] = '\0';
		ft_strpluswithoutt(s, d, i, all);
	}
	free(d);
	return (0);
}

void	ft_strpluswitht(char *s, char *d, int i, t_flags *all)
{
	ft_memcpy(d, s, all->precision);
	i = ft_strlen(d);
	while (all->width > i)
	{
		ft_putchar1(' ', all);
		i++;
	}
	ft_putstr1(d, all);
}

void	ft_strpluswithoutt(char *s, char *d, int i, t_flags *all)
{
	int j;

	j = i;
	while (all->width > i && all->fl3)
	{
		ft_putchar1('0', all);
		i++;
	}
	while (all->width > i && !(all->fl3))
	{
		ft_putchar1(' ', all);
		i++;
	}
	ft_memcpy(d, s, j);
	ft_putstr1(d, all);
}
