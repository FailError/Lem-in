/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 22:34:25 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_str(va_list args, t_flags *all)
{
	char	*s;
	char	*d;
	int		i;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	i = ft_strlen(s);
	d = all->t ? (char *)malloc(sizeof(char) * all->precision + 1) :
		(char *)malloc(sizeof(char) * i + 1);
	if (all->t)
		d[all->precision] = '\0';
	else if (!(all->t))
		d[i] = '\0';
	if (all->t && all->precision == 0 && all->width == 0)
		return (0);
	if (all->t && all->fl2)
		ft_strwitht(s, d, i, all);
	else if (!(all->t))
		ft_strwithoutt(s, d, i, all);
	free(d);
	return (0);
}

void	ft_strwitht(char *s, char *d, int i, t_flags *all)
{
	ft_memcpy(d, s, all->precision);
	i = ft_strlen(d);
	ft_putstr1(d, all);
	while (all->width > i)
	{
		ft_putchar1(' ', all);
		i++;
	}
}

void	ft_strwithoutt(char *s, char *d, int i, t_flags *all)
{
	ft_memcpy(d, s, i);
	ft_putstr1(d, all);
	while (all->width > i)
	{
		ft_putchar1(' ', all);
		i++;
	}
}
