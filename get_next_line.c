/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/06/05 11:49:11 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	replace_rest(char *rest,
			enum e_line_status line_status)
{
	if (line_status == complete_line)
	{
		ft_strlcpy(rest, ft_strchr(rest, '\n') + 1,
			ft_strlen(ft_strchr(rest, '\n')) + 1);
	}
	else
	{
		ft_bzero(rest, BUFFER_SIZE + 1);
	}
}

static enum e_line_status	read_line_from_file(char **line, char *rest)
{
	char				buffer[BUFFER_SIZE + 1];
	enum e_line_status	line_status;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	line_status = read_line_until_new_line(line, buffer);
	if (line_status == uncomplete_line)
	{
		line_status = fill_line_from_src(line, buffer);
	}
	return (line_status);
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
		*line = ft_strnjoin(*line, src, ft_strlen(src));
		line_status = uncomplete_line;
	}
	if (*line == NULL)
	{
		line_status = error;
	}
	return (line_status);
}

static enum e_line_status	read_line_from_rest(char **line, char *rest)
{
	enum e_line_status	line_status;

	line_status = fill_line_from_src(line, rest);
	replace_rest(rest, line_status);
	return (line_status);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	rest[BUFFER_SIZE + 1] = {0};

	if (read_line_from_rest(&line, rest) == uncomplete_line)
	{
		read_line_from_file(&line, rest);
	}
	return (line);
}

// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }
