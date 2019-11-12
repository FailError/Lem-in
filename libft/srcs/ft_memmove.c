/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:45:33 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *s1;
	unsigned char *s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (s1 == s2)
		return (NULL);
	if (s1 <= s2 || s1 >= (s2 + len))
	{
		while (len--)
			*s1++ = *s2++;
	}
	else
	{
		s1 += len - 1;
		s2 += len - 1;
		while (len--)
			*s1-- = *s2--;
	}
	return (dst);
}
