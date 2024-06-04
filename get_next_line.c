/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/06/04 14:38:31 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static enum e_line_satus	fill_line(char **line,char *buffer)
{

}

static enum e_line_satus	add_rest(char **line, char *rest)
{
	const int	p_new_line = ft_strchr(rest, '\n') - rest;

	fill_new_line(line, rest);
	strlcpy(rest, ft_strchr(rest, '\n'), p_new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	static char	rest[BUFFER_SIZE + 1] = {0};

	if (add_rest(&line, rest) == complete_line)
	{
		if (fill_line(&line, buffer) == complete_line)
		{
			fill_rest(rest);
		}
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
