/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:22:43 by kbessa            #+#    #+#             */
/*   Updated: 2019/10/27 16:24:12 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_new_line(char **s, char **line, int fd, int ret)
{
	char		*tmp;
	int			len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			iread;
	char		*tmp;
	static char	*str[255];

	if (fd < 0 || line == NULL)
		return (-1);
	while ((iread = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[iread] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		tmp = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (iread < 0)
		return (-1);
	else if (iread == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	return (ft_new_line(str, line, fd, iread));
}
