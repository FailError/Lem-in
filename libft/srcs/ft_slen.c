/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:25:17 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_slen(const char *s1, const char *s2)
{
	unsigned long	ret;

	ret = 0;
	while (*s1 && ft_strchr(s2, *s1++))
		ret++;
	return (ret);
}
