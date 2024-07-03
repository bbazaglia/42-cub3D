/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:48:02 by bbazagli          #+#    #+#             */
/*   Updated: 2023/10/24 15:43:43 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new;
	unsigned int	newlen;
	unsigned int	s1len;
	unsigned int	s2len;
	int				i;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newlen = s1len + s2len;
	new = (char *)malloc(sizeof(char) * (newlen + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	i = -1;
	while (s2[++i])
		new[i + s1len] = s2[i];
	new[newlen] = '\0';
	return (new);
}
