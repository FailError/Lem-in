/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:23:44 by kbessa            #+#    #+#             */
/*   Updated: 2019/12/04 20:01:24 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				**ft_strsplit(char *s, char c)
{
	size_t			i;
	size_t			n;
	int				p;
	char			**tab;

	if (!s)
		return (NULL);
	i = 0;
	p = 0;
	tab = (char **)ft_memalloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	while (s[i])
	{
		while (s[i] == c)
			i++;
		n = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > n)
		{
			tab[p] = ft_strndup(s + n, i - n);
			p++;
		}
	}
	return (tab);
}
