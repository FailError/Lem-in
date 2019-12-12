#include "lem-in.h"

unsigned		ft_atoi_ants(char *str)
{
	unsigned	ants;
	unsigned	i;

	ants = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			ants = (ants * 10) + str[i] - '0';
			i++;
		}
		else
			ft_error_str("\x1B[31mError\033[0m");
	}
	i == 0 || i > 10 || ants > INT_MAX ? ft_error_str("\x1B[31mError\033[0m") : 0;
	free(str);
	str = NULL;
	return (ants);
}

void	number_of_ants(t_all *all, int fd)
{
	char *str;

	str = NULL;
	get_next_line(fd, &str);
	ft_putstr(str);
	all->number_of_ants = ft_atoi_ants(str);
}
