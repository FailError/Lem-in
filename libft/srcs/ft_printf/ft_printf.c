/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:08:08 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	all;

	va_start(args, format);
	ft_bzero(&all, sizeof(t_flags));
	while (*format)
	{
		while (*format != '%' && *format != '\0')
		{
			ft_putchar1(*format, &all);
			format += 1;
		}
		if (*format == '%')
			ft_ifproc(&format, &all, args);
	}
	va_end(args);
	return (all.re);
}

int		ft_ifproc(const char **format, t_flags *all, va_list args)
{
	if (ft_doubleproc(all, format) == 0)
	{
		while (**format != '%' && **format != '\0')
		{
			ft_putchar1(**format, all);
			*format += 1;
		}
	}
	else
	{
		ft_checkproc(format, all);
		if (all->spec == '\0')
			ft_nullspec(format, all);
		else
		{
			*format += 1;
			ft_checkstruct(args, all);
			all->procent = 0;
		}
	}
	return (0);
}

int		ft_nullspec(const char **format, t_flags *all)
{
	if (**format)
	{
		if (**format == '%')
		{
			*format += 1;
			if (all->fl2)
			{
				ft_putchar1('%', all);
				while (all->width-- > 1)
					ft_putchar1(' ', all);
			}
			else
				ft_nullspecplus(all);
		}
	}
	return (0);
}

int		ft_doubleproc(t_flags *all, const char **format)
{
	if (**format == '%')
	{
		*format += 1;
		if (**format == '\0')
			return (0);
		else
			*format -= 1;
	}
	while (**format == '%')
	{
		*format += 1;
		all->procent += 1;
	}
	if (ft_divisionproc(all) == 0)
		return (0);
	else
		return (1);
}

int		ft_divisionproc(t_flags *all)
{
	if (all->procent % 2 == 0)
	{
		while (all->procent != 0)
		{
			ft_putchar1('%', all);
			all->procent -= 2;
		}
		return (0);
	}
	else
	{
		while (all->procent != 1)
		{
			ft_putchar1('%', all);
			all->procent -= 2;
		}
		return (1);
	}
}
