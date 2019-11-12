/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:59:24 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int c;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		c = -1 * n;
	}
	else
		c = n;
	if (c >= 10)
	{
		ft_putnbr_fd(c / 10, fd);
	}
	ft_putchar_fd(c % 10 + 48, fd);
}
