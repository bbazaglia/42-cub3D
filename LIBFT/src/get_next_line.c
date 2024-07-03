/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:12:05 by bbazagli          #+#    #+#             */
/*   Updated: 2024/02/20 10:37:26 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_fd(int fd, char *unfiltered_line, int *bytes_read)
{
	char	*buffer;
	char	*temp;

	if (!unfiltered_line)
		unfiltered_line = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	*bytes_read = 1;
	while (!ft_strchr(unfiltered_line, '\n') && *bytes_read != 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(buffer);
			free(unfiltered_line);
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		temp = unfiltered_line;
		unfiltered_line = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (unfiltered_line);
}

char	*ft_filter_line(char *unfiltered_line)
{
	int		i;
	char	*filtered_line;

	i = 0;
	if (!unfiltered_line[i])
		return (NULL);
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
		i++;
	filtered_line = ft_calloc(i + 2, sizeof(char));
	if (!filtered_line)
		return (NULL);
	i = 0;
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
	{
		filtered_line[i] = unfiltered_line[i];
		i++;
	}
	if (unfiltered_line[i] == '\n')
	{
		filtered_line[i] = unfiltered_line[i];
		i++;
	}
	return (filtered_line);
}

char	*ft_rest_unfiltered(char *unfiltered_line)
{
	int		i;
	int		j;
	char	*rest_line;

	i = 0;
	while (unfiltered_line[i] && unfiltered_line[i] != '\n')
		i++;
	if (!unfiltered_line[i])
	{
		free(unfiltered_line);
		return (NULL);
	}
	rest_line = ft_calloc(ft_strlen(unfiltered_line) - i + 1, sizeof(char));
	if (!rest_line)
		return (NULL);
	i++;
	j = 0;
	while (unfiltered_line[i])
		rest_line[j++] = unfiltered_line[i++];
	free(unfiltered_line);
	return (rest_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*unfiltered_line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (unfiltered_line)
			free(unfiltered_line);
		return (NULL);
	}
	unfiltered_line = ft_read_fd(fd, unfiltered_line, &bytes_read);
	if (!unfiltered_line)
		return (NULL);
	next_line = ft_filter_line(unfiltered_line);
	unfiltered_line = ft_rest_unfiltered(unfiltered_line);
	if (next_line == NULL && bytes_read == 0)
	{
		free(unfiltered_line);
		return (NULL);
	}
	return (next_line);
}
