/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:48:58 by bbazagli          #+#    #+#             */
/*   Updated: 2023/10/24 15:43:47 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	total_len;
	size_t	i;

	if (dst == NULL)
		dst_len = 0;
	else
		dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	total_len = src_len + dst_len;
	i = 0;
	if (size > dst_len)
	{
		while (src[i] && dst_len < (size - 1))
		{
			dst[dst_len] = src[i];
			dst_len++;
			i++;
		}
		dst[dst_len] = '\0';
		return (total_len);
	}
	return (src_len + size);
}
