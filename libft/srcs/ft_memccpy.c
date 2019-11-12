/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 21:29:41 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
int c, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	unsigned char		cc;

	cc = (unsigned char)c;
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (n--)
	{
		*s1++ = *s2++;
		if (*(s1 - 1) == cc)
			return ((void *)s1);
	}
	return (NULL);
}
