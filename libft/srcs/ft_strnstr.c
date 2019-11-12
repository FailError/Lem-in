/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:13:28 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	int		result;

	if (!(*haystack))
		return (NULL);
	if ((*needle == '\0') || (*haystack == '\0'))
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	result = 1;
	while (nlen <= len && *haystack != '\0'
		&& (result = ft_strncmp(haystack, needle, nlen)))
	{
		len--;
		haystack++;
	}
	if (result != '\0')
		return (NULL);
	else
		return ((char *)haystack);
}
