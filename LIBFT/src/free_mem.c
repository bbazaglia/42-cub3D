
#include "libft.h"

void	free_mem(t_list **list)
{
	t_list	*cur;

	while (*list)
	{
		cur = (*list)->next;
		if ((*list)->content)
		{
			free((*list)->content);
			(*list)->content = NULL;
		}
		free(*list);
		*list = NULL;
		*list = cur;
	}
}