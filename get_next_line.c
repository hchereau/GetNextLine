/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <hchereau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/05/26 23:55:59 by hchereau         ###   ########.fr       */
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

static int	get_line(char *buffer, char *line, int fd, int bytes_read)
{
	int	i_new_line;

	i_new_line = find_char(buffer, '\n');
	while (i_new_line != '\n' && bytes_read > 0)
	{
		ft_strnjoin(line, buffer, BUFFER_SIZE);
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
}

int	fill_line(char *buffer, char *line, int fd)
{
	static char	rest[BUFFER_SIZE + 1] = {0};
	int			bytes_read;
	int			is_success;

	if (rest[0] != '\0')
	{
		ft_strlcpy(rest, line, ft_strlen(rest));
	}
	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		return (EXIT_FAILURE);
	}
	is_success = get_line(buffer, line, fd, bytes_read);
	return (is_success);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			is_error;

	line = NULL;
	if (fd >= 0)
	{
		is_error = fill_line(buffer, line, fd);
		if (is_error)
		{
			return (NULL);
		}
		fill_rest(buffer);
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
