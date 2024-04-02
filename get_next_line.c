/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imback <imback@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:14:28 by imback            #+#    #+#             */
/*   Updated: 2024/04/02 14:13:28 by imback           ###   ########.fr       */
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

static int	get_new_line(const char *str, size_t size)
{
	int	i;

	i = 0;
	while (i < size && str[i] != '\n')
	{
		++i;
	}
	return (i);
}

static void	add_rest(char	**dest, char *rest, const size_t size)
{
	if (rest[0] != '\0')
	{
		add_str(dest, rest, size);
	}
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE] = {0};
	char		buffer[BUFFER_SIZE];
	char		*line;
	int			bytes_read;
	int			i_newline;

	add_rest(&line, rest, ft_strlen(rest));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	i_newline = get_new_line(buffer, bytes_read);
	while (i_newline == BUFFER_SIZE - 1 && bytes_read > 0)
	{
		add_str(&line, buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		i_newline = get_new_line(buffer, bytes_read);
	}
	if (i_newline < bytes_read)
	{
		add_str(line, buffer, i_newline + 1);
		ft_strlcpy(rest, buffer + i_newline + 1, bytes_read - i_newline - 1);
	}
	return line;
}

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
