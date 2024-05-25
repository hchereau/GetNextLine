/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/05/25 18:50:42 by hucherea         ###   ########.fr       */
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
	if (s[i] == c)
		return (i);
	return (-1);
}

static void	last_fill(char *line, char *buffer)
{
	const int	line_len = ft_strlen(line);
	const int	i_new_line = find_char();
	char		*final_line;


}


int	fill_line(char *buffer, char *line, int fd)
{
	int	i;
	int	bytes_read;
	int	index_nl;

	i = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		return (EXIT_FAILURE);
	}
	while (bytes_read != 0 && !find_char(line, '\n') == -1)
	{
		ft_strjoin(line, buffer);
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	last_fill(line, buffer);
	return (EXIT_SUCCESS);
}


char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE] = {0};
	char		buffer[BUFFER_SIZE];
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
		print_line(line);
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
