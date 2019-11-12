/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatprecnull1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 09:11:50 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**точность 0 float
*/

int				ft_precnull(t_flags *all, double d)
{
	long long int	i;
	int				counter;
	int				lastnum;
	long long		ii;

	lastnum = ft_lastnum(d);
	i = 0;
	all->sign = ft_sign(d);
	counter = all->sign ? 1 : 0;
	ii = ft_nolnolnol(d, lastnum);
	i = ii;
	config(all, &counter, i);
	if (all->fl2)
		ft_flminus(all, i, counter);
	else
		ft_flplus(all, i, counter);
	return (0);
}

int				ft_lastnum(double a)
{
	long long int	b;
	double			c;
	int				qq;

	b = (long long)a;
	c = 10 * (a - (double)b);
	b = c < 0 ? (long long)-c : (long long)c;
	b = b >= 5 ? 1 : 0;
	qq = (int)b;
	return (qq);
}

int				ft_sign(double t)
{
	int				sign;
	unsigned long	*ptr;

	ptr = (unsigned long *)&t;
	sign = *ptr >> 63;
	return (sign);
}

long long int	ft_nolnolnol(double t, int lastnum)
{
	if (t == -0 || t == 0)
	{
		t = 0;
	}
	else
	{
		t = t < 0 ? -t : t;
	}
	if (lastnum)
		t += 1;
	return ((long long)t);
}

t_flags			*config(t_flags *all, int *counter, long long int i)
{
	if (all->fl2 && all->fl3)
		all->fl3 = '\0';
	if (all->fl1 && all->fl5)
		all->fl5 = '\0';
	if (all->fl4)
		*counter += 1;
	if (all->fl1 && all->sign == 0)
		*counter += 1;
	if (all->fl5 && all->sign == 0)
		*counter += 1;
	*counter += dlwidthfloat(i);
	return (all);
}
