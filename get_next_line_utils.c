/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:15:12 by imback            #+#    #+#             */
/*   Updated: 2024/05/25 13:57:55 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
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

char	*ft_strjoin(char const *s1, char const *s2)
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
	join = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (join != NULL)
	{
		if (s1 != NULL)
			ft_strlcpy(join, s1, size1 + 1);
		if (s2 != NULL)
			ft_strlcpy(join + size1, s2, size2 + 1);
	}
	return (join);
}

static void	*ft_memset(void	*s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((uint8_t *)s)[i] = (uint8_t)c;
		++i;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
