/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 09:29:55 by bbazagli          #+#    #+#             */
/*   Updated: 2023/10/24 15:44:12 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	trimlen;
	char	*trimstr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[start]) && start < end)
		start++;
	while (ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	trimlen = end - start;
	trimstr = (char *)malloc(trimlen + 1);
	if (trimstr == NULL)
		return (NULL);
	i = -1;
	while (++i < trimlen)
		trimstr[i] = s1[start + i];
	trimstr[i] = '\0';
	return (trimstr);
}
