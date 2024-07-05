/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:33:56 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 13:35:42 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			count++;
			while (s[i] && !ft_isspace(s[i]))
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

char	**ft_write_words(char **words, char const *s)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (!ft_isspace(s[len]) && s[len])
			len++;
		words[i] = (char *)malloc(len * sizeof(char) + 1);
		if (words[i] == NULL)
			return (ft_free_split(words));
		words[i][len] = '\0';
		while (len > 0)
		{
			words[i][len - 1] = s[len - 1];
			len--;
		}
		while (!ft_isspace(*s) && *s)
			s++;
		while (ft_isspace(*s) && *s)
			s++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s)
{
	char	**arr;
	size_t	num_words;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s);
	arr = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (arr == NULL)
		return (NULL);
	while (ft_isspace(*s) && *s)
		s++;
	arr = ft_write_words(arr, s);
	arr[num_words] = NULL;
	return (arr);
}
