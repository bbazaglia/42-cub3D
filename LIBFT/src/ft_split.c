/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:19:34 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 13:19:56 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	*ft_free_split(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

char	**ft_write_words(char **words, char const *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (s[len] != c && s[len])
			len++;
		words[i] = allocate_mem(len + 1, sizeof(char));
		if (words[i] == NULL)
			return (ft_free_split(words));
		words[i][len] = '\0';
		while (len > 0)
		{
			words[i][len - 1] = s[len - 1];
			len--;
		}
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	num_words;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	arr = allocate_mem(num_words + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (*s == c && *s)
		s++;
	arr = ft_write_words(arr, s, c);
	arr[num_words] = NULL;
	return (arr);
}
