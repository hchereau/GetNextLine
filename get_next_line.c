/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/05/27 15:54:33 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static int	find_char(const char *s, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	while (s[i] != c && s[i] != '\0')
	{
		++i;
	}
	return (i);
}

static char	*get_line(char *buffer, char *line, int fd, int bytes_read)
{
	int	i_new_line;

	i_new_line = find_char(buffer, '\n');
	while (buffer[i_new_line] != '\n' && bytes_read > 0)
	{
		line = ft_strnjoin(line, buffer, BUFFER_SIZE);
		if (line == NULL)
		{
			return (NULL);
		}
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		i_new_line = find_char(buffer, '\n');
	}
	if (buffer[i_new_line] == '\n')
	{
		line = ft_strnjoin(line, buffer, i_new_line + 1);
		if (line == NULL)
		{
			return (NULL);
		}
	}
	return (line);
}

static char	*fill_line(char *buffer, char *line, char *rest, int fd)
{
	int	bytes_read;
	int	index_rest;

	index_rest = find_char(rest, '\n');
	if (rest[0] != '\0')
	{
		line = ft_strnjoin(line, rest, index_rest + 1);
		if (rest[index_rest] == '\n')
		{
			ft_strlcpy(rest, rest + index_rest + 1,
				ft_strlen(rest) - index_rest);
			return (line);
		}
		else
			ft_bzero(rest, BUFFER_SIZE);
	}
	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		return (NULL);
	}
	line = get_line(buffer, line, fd, bytes_read);
	return (line);
}

static void	fill_rest(char *buffer, char *rest)
{
	const int	index = find_char(buffer, '\n');

	ft_bzero(rest, BUFFER_SIZE);
	ft_strlcpy(rest, buffer + index + 1, ft_strlen(buffer + index));
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	rest[BUFFER_SIZE + 1] = {0};
	char		*line;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	line = NULL;
	if (fd >= 0)
	{
		line = fill_line(buffer, line, rest, fd);
		if (line == NULL)
		{
			return (NULL);
		}
		else if (rest[0] == '\0')
		{
			fill_rest(buffer, rest);
		}
	}
	return (line);
}

// #include <fcntl.h>
// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int	fd;
// 	fd = open("test.txt", O_RDONLY);
// 	printf("line1 = [%s]\n", get_next_line(fd));
// 	printf("line2 = [%s]\n", get_next_line(fd));
// 	printf("line3 = [%s]\n", get_next_line(fd));
// 	printf("line4 = [%s]\n", get_next_line(fd));
// 	printf("line5 = [%s]\n", get_next_line(fd));
// 	printf("line6 = [%s]\n", get_next_line(fd));
// 	close(fd);
// }


