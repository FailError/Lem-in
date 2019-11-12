/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:34:00 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/30 23:12:58 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_word_count(char *s, char c)
{
	unsigned int	i;
	unsigned int	cntr;

	i = 0;
	cntr = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && ((s[i] >= '0' && s[i] <= '9') || s[i] == '-'))
			cntr++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (int)(cntr);
}
