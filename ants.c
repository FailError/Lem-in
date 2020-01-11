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
	i == 0x0 || i > 0xA || ants > 0x7FFFFFFF ? ft_error_str("\x1B[31mError\033[0m") : 0;
	free(str);
	return (ants);
}

void	number_of_ants(t_all *all, int fd, t_calc *calc)
{
	char *str;

	str = NULL;
	get_next_line(fd, &str);
	ft_putstr(str);
	all->number_of_ants = ft_atoi_ants(str);
	calc->number_of_ants = (int)all->number_of_ants;
}
