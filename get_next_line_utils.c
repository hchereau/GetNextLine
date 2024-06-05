/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:15:12 by imback            #+#    #+#             */
/*   Updated: 2024/06/05 18:33:12 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		++len;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strnjoin(char *s1, char const *s2, const size_t size)
{
	char	*join;
	size_t	size1;
	size_t	size2;

	size1 = 0;
	size2 = 0;
	if (s1 != NULL)
		size1 = ft_strlen(s1);
	if (s2 != NULL)
		size2 = ft_strlen(s2);
	if (size2 > size)
		size2 = size;
	join = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (join != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(join, s1, size1 + 1);
		if (s2 != NULL)
			ft_strlcpy(join + size1, s2, size2 + 1);
	}
	free(s1);
	return (join);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((uint8_t *)s)[i] = (uint8_t) '\0';
		++i;
	}
}

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s != c && *s != '\0')
		++s;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

enum e_line_status	read_line_until_new_line(char **line, char *buffer, int fd)
{
	enum e_line_status	line_status;
	int					bytes_read;

	line_status = uncomplete_line;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0 && ft_strchr(buffer, '\n' ) == NULL)
	{
		*line = ft_strnjoin(*line, buffer, bytes_read);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (ft_strchr(buffer, '\n') == NULL)
	{
		line_status = complete_line;
	}
	if (bytes_read < 0)
	{
		line_status = error_line;
	}
	return (line_status);
}
