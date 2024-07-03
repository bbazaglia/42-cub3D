/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:30:57 by bbazagli          #+#    #+#             */
/*   Updated: 2023/10/24 15:44:08 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		len;

	ptr = (char *)s;
	len = ft_strlen(ptr);
	while (len >= 0)
	{
		if (ptr[len] == (unsigned char)c)
			return (&ptr[len]);
		len--;
	}
	return (NULL);
}
