/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 22:40:20 by Kwillum           #+#    #+#             */
/*   Updated: 2020/05/09 22:40:44 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*p;
	char	*start;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s2) + ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	start = p;
	while (len-- && *s1)
		*p++ = *s1++;
	len++;
	while (len-- && *s2)
		*p++ = *s2++;
	*p = '\0';
	return (start);
}

size_t	ft_strlcpy(char *d, const char *src, size_t n)
{
	const char	*s;

	s = src;
	if (n != 0)
	{
		while (--n && *s)
			*d++ = *s++;
		*d = '\0';
	}
	while (*s)
		s++;
	return (s - src);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	return ((char *)NULL);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	char	*start;

	p = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!(p))
		return (NULL);
	start = p;
	while (*s)
		*p++ = *s++;
	*p = '\0';
	return (start);
}
