/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/06/05 19:02:22 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	replace_rest(char *rest,
			enum e_line_status line_status)
{
	const char	*end_line = ft_strchr(rest, '\n');

	if (line_status == complete_line)
	{
		ft_strlcpy(rest, end_line + 1,
			ft_strlen(end_line) + 1);
	}
	else
	{
		ft_bzero(rest, BUFFER_SIZE + 1);
	}
}

static enum e_line_status	fill_line_from_src(char **line, char *src)
{
	enum e_line_status	line_status;
	const char			*new_line = ft_strchr(src, '\n');

	if (new_line != NULL)
	{
		*line = ft_strnjoin(*line, src, new_line - src + 1);
		line_status = complete_line;
	}
	else
	{
		*line = ft_strnjoin(*line, src, ft_strlen(src) + 1);
		line_status = uncomplete_line;
	}
	if (*line == NULL)
	{
		line_status = error_line;
	}
	return (line_status);
}

static void	fill_rest_from_buffer(char *buffer, char *rest,
	enum e_line_status line_status)
{
	const char	*end_line = ft_strchr(buffer, '\n');

	if (line_status == complete_line)
	{
		ft_strlcpy(rest, end_line + 1,
			(buffer + ft_strlen(buffer)) - end_line);
	}
}

static enum e_line_status	read_line_from_file(char **line, char *rest, int fd)
{
	char				buffer[BUFFER_SIZE + 1];
	enum e_line_status	line_status;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	line_status = read_line_until_new_line(line, buffer, fd);
	if (line_status == uncomplete_line)
	{
		line_status = fill_line_from_src(line, buffer);
		fill_rest_from_buffer(buffer, rest, line_status);
	}
	return (line_status);
}

static enum e_line_status	read_line_from_rest(char **line, char *rest)
{
	enum e_line_status	line_status;

	line_status = uncomplete_line;
	if (ft_strlen(rest) != 0)
	{
		line_status = fill_line_from_src(line, rest);
		replace_rest(rest, line_status);
	}
	return (line_status);
}

char	*get_next_line(int fd)
{
	char				*line;
	static char			rest[FOPEN_MAX][BUFFER_SIZE + 1] = {0};
	enum e_line_status	line_status;

	line = NULL;
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	line_status = read_line_from_rest(&line, rest[fd]);
	if (line_status == uncomplete_line)
	{
		line_status = read_line_from_file(&line, rest[fd], fd);
	}
	if (line_status == error_line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }
