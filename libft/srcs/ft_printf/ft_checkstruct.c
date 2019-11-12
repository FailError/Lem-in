/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkstruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:13:16 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_checkstruct(va_list args, t_flags *all)
{
	if (all->spec == 0)
		return (0);
	if ((all->spec == 'd' || all->spec == 'i') && all->fl2 == '\0')
		ft_decimal(args, all);
	if ((all->spec == 'd' || all->spec == 'i') && all->fl2 == '-')
		ft_decimalmin(args, all);
	all->spec == 's' && all->fl2 ? ft_str(args, all) : 0;
	all->spec == 's' && !(all->fl2) ? ft_strplus(args, all) : 0;
	all->spec == 'c' ? ft_charc(args, all) : 0;
	all->spec == 'p' ? ft_point(args, all) : 0;
	all->spec == 'o' && all->fl2 == '\0' ? ft_odecimal(args, all) : 0;
	all->spec == 'o' && all->fl2 == '-' ? ft_odecimalmin(args, all) : 0;
	all->spec == 'u' && all->fl2 == '\0' ? ft_udecimal(args, all) : 0;
	all->spec == 'u' && all->fl2 == '-' ? ft_udecimalmin(args, all) : 0;
	all->spec == 'x' && all->fl2 == '\0' ? ft_xhex(args, all) : 0;
	all->spec == 'x' && all->fl2 == '-' ? ft_xhexmin(args, all) : 0;
	all->spec == 'X' && all->fl2 == '\0' ? ft_xhexx(args, all) : 0;
	all->spec == 'X' && all->fl2 == '-' ? ft_xhexxmin(args, all) : 0;
	all->spec == 'f' ? ft_float(args, all) : 0;
	return (0);
}

void	ft_checkspec(t_flags *all, const char **format)
{
	if (**format)
	{
		if (**format == 's' || **format == 'c' || **format == 'p'
			|| **format == 'd'
			|| **format == 'i' || **format == 'o' || **format == 'u'
			|| **format == 'x'
			|| **format == 'X' || **format == 'f')
		{
			all->spec = **format;
		}
		else
			all->spec = 0;
	}
	else
		all->spec = 0;
}

void	ft_flagstr(const char **format, t_flags *all)
{
	ft_putstr1(*format, all);
	*format += ft_strlen(*format);
}

int		ft_whileee(const char **format)
{
	if (((**format != '%' && **format != 'd' && **format != 's' &&
		**format != 'p' && **format != 'c' && **format != 'i' &&
		**format != 'o' && **format != 'u' && **format != 'x' &&
		**format != 'X' && **format != 'f') && **format != '.' &&
		!(**format >= '1' && **format <= '9') && **format != 'l' &&
		**format != 'L' && **format != 'h' && **format != 'H' &&
		**format != 'D' && **format != 'A' && **format != 'e' &&
		**format != 'G' && **format != 'F' && **format != 'E'
		&& **format != 'a' && **format != 'g' && **format != '*'))
		return (1);
	else
		return (0);
}
