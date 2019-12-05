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
			ants = (ants * 10) + (str[i] - '0');
			i++;
		}
		else
			ft_error_str("Error");
	}
	i == 0 || i > 10 || ants > 2147483647 ? ft_error_str("Error") : 0;
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
	ifcomments(str);
	all->number_of_ants = ft_atoi_ants(str);
}
