/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 09:33:29 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**ласт число в массиве == 9
**и след число >= 5
*/

void			ft_fninelastnum(t_f *f, t_flags *all, char *v)
{
	while (f->accur > f->c && v[f->len - 1] == '9')
	{
		v[f->len - 1] = '0';
		f->accur--;
		f->y++;
		f->len--;
	}
	if (v[f->len - 1] != '.')
		v[f->len - 1] += 1;
	if (f->y == f->i)
		v[f->c1 - 2] += 1;
	config2(all, v);
	if (all->fl2 == '\0')
		ft_flplus2(all, v);
	else
		ft_flminus2(all, v);
	free(v);
}

/*
**полезное
*/

void			ft_fthreeother(t_flags *all, char *v)
{
	config2(all, v);
	if (all->fl2 == '\0')
		ft_flplus2(all, v);
	else
		ft_flminus2(all, v);
	free(v);
}
