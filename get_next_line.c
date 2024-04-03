/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/04/03 19:03:44 by imback           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_str(char **dest, const char *src, const size_t size)
{
	char	*dest_free;

	dest_free = *dest;
	*dest = ft_strnjoin(*dest, src, size);
	free(dest_free);
}

static void	add_rest(char	**dest, char *rest, const size_t size)
{
	if (rest[0] != '\0')
	{
		add_str(dest, rest, size);
	}
}

static void	fill_without_newline(t_file_data *line_data, char **line, int fd)
{
	while (line_data->i_newline == BUFFER_SIZE && line_data->bytes_read > 0)
	{
		add_str(line, line_data->buffer, line_data->bytes_read);
		line_data->bytes_read = read(fd, line_data->buffer, BUFFER_SIZE);
		line_data->i_newline
			= get_new_line(line_data->buffer, line_data->bytes_read);
	}
}

static void	fill_line(char **line, char *rest, int fd)
{
	t_file_data	line_data;
	size_t		i_newline_rest;

	i_newline_rest = get_new_line(rest, ft_strlen(rest));
	if (rest[i_newline_rest] != '\n')
	{
		add_rest(line, rest, i_newline_rest);
		line_data.bytes_read = read(fd, line_data.buffer, BUFFER_SIZE);
		line_data.i_newline
			= get_new_line(line_data.buffer, line_data.bytes_read);
		fill_without_newline(&line_data, line, fd);
		if (line_data.i_newline < line_data.bytes_read)
		{
			add_str(line, line_data.buffer, line_data.i_newline + 1);
			ft_strlcpy(rest, line_data.buffer + line_data.i_newline + 1,
				line_data.bytes_read - line_data.i_newline);
		}
	}
	else
	{
		add_rest(line, rest, i_newline_rest + 1);
		ft_strlcpy(rest, rest + i_newline_rest + 1,
			BUFFER_SIZE - i_newline_rest);
	}
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE] = {0};
	char		*line;

	line = NULL;
	fill_line(&line, rest, fd);
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

// int	main(void)
// {
// 	char *str = "salutbonjour";
// 	printf("\n%d\n", get_new_line(str, ft_strlen(str)));
// }

// int	main(void)
// {
// 	char	*dest;

// 	dest = (char *)malloc(6 * sizeof(char));
// 	strncpy(dest, "salut", 5);
// 	dest[6] = '\0';
// 	add_str(&dest, "bonjour", 7);
// 	printf("\n%s\n", dest);
// 	free(dest);
// }
