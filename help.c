#include "lem-in.h"

void	ft_error_str(char *str)
{
	ft_putstr(str);
	exit(-1);
}

t_list	*ft_lstnew2(void const *content)
{
	t_list	*newl;

	if (!(newl = (t_list *)ft_memalloc(sizeof(*newl))))
		return (NULL);
	if (content == NULL)
	{
		newl->content = NULL;
		newl->content_size = 0;
	}
	else
	{
		newl->content = (void *)content;
		newl->content_size = sizeof(void *);
	}
	newl->next = NULL;
	return (newl);
}
