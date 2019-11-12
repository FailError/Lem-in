/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:05:26 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *p1;
	unsigned char *p2;

	p1 = (unsigned char*)s1;
	p2 = (unsigned char*)s2;
	while (n > 0 && *p1 == *p2)
	{
		p1++;
		p2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*p1 - *p2);
}
