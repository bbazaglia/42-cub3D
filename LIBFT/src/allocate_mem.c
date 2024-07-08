#include "libft.h"

t_list	**get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}

void	collect_mem(void *content)
{
	ft_lstadd_back(get_mem_address(), ft_lstnew(content));
}

void	*allocate_mem(size_t nmemb, size_t size)
{
	void	*content;

	content = ft_calloc(nmemb, size);
	if (content == NULL)
		exit(EXIT_FAILURE);
	collect_mem(content);
	return (content);
}