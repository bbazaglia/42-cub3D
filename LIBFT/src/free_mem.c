/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:00:05 by cogata            #+#    #+#             */
/*   Updated: 2024/07/22 17:00:25 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
