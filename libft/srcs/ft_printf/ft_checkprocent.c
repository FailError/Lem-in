/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checprocent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:01:47 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_checkproc(const char **format, t_flags *all)
{
	ft_bzero2(all);
	ft_typesflags(format, all);
	while (**format >= '0' && **format <= '9')
	{
		all->width = ft_width(*format);
		*format += (all->width ? dlwidth(all->width) : 1);
	}
	if (**format == '.')
	{
		all->t = **format;
		*(format) += 1;
		while (**format >= '0' && **format <= '9')
		{
			all->precision = ft_width(*format);
			*(format) += dlwidth(all->precision) ? dlwidth(all->precision) : 1;
		}
	}
	ft_dlina(format, all);
	if (**format == '%')
		return (0);
	else
		ft_checkspec(all, format);
	return (0);
}

void		ft_bzero2(t_flags *all)
{
	all->fl1 = '\0';
	all->fl2 = '\0';
	all->fl3 = '\0';
	all->fl4 = '\0';
	all->fl5 = '\0';
	all->t = '\0';
	all->width = 0;
	all->precision = 0;
	all->dlina = '\0';
	all->spec = '\0';
	all->sign = 0;
	all->counter = 0;
	all->help = 0;
	all->y = 0;
}

void		ft_typesflags(const char **format, t_flags *all)
{
	while (ft_whileee(format))
	{
		if (**format == '+')
			all->fl1 = **format;
		else if (**format == ' ')
			all->fl5 = **format;
		else if (**format == '-')
			all->fl2 = **format;
		else if (**format == '0')
			all->fl3 = **format;
		else if (**format == '#')
			all->fl4 = **format;
		else
		{
			ft_flagstr(format, all);
			return ;
		}
		*(format) += 1;
	}
}

int			ft_width(const char *format)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = ft_len(format);
	if (!(s = (char *)malloc(i * sizeof(int))))
		return (0);
	while (i > 1)
	{
		s[j++] = *format++;
		i--;
	}
	s[j] = '\0';
	if (ft_strchr(s, '$'))
	{
		free(s);
		return (0);
	}
	i = ft_atoi(s);
	free(s);
	return (i);
}

void		ft_dlina(const char **format, t_flags *all)
{
	if (**format == 'h' || **format == 'l')
	{
		all->dlina = **format;
		*(format) += 1;
		if (**format == 'h')
		{
			all->dlina = 'H';
			*(format) += 1;
		}
		else if (**format == 'l')
		{
			all->dlina = 'L';
			*(format) += 1;
		}
	}
	else if (**format == 'L')
	{
		all->dlina = 'D';
		*(format) += 1;
	}
}
