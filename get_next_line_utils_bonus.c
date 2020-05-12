/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 22:40:20 by Kwillum           #+#    #+#             */
/*   Updated: 2020/05/12 18:46:55 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_list	*ft_lstnew(void *content, int fd)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(t_list));
	if (!element)
	{
		free(content);
		return (NULL);
	}
	element->content = content;
	element->fd = fd;
	element->next = NULL;
	return (element);
}
