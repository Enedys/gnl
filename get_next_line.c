/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:28:42 by Kwillum           #+#    #+#             */
/*   Updated: 2020/05/10 12:45:02 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_lstnew(void *content, int fd)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = content;
	element->fd = fd;
	element->next = NULL;
	return (element);
}

static char		*ft_get_residual(t_list **residual, int fd)
{
	t_list	*tmp;
	t_list	*swap;

	if (!(*residual))
	{
		*residual = ft_lstnew(ft_strdup(""), fd);
		return ((*residual)->content);
	}
	tmp = *residual;
	while (tmp->next && tmp->fd < fd)
	{
		swap = tmp;
		tmp = tmp->next;
	}
	if (tmp->fd == fd)
		return ((char *)tmp->content);
	if (!(tmp->next))
	{
		tmp->next = ft_lstnew(ft_strdup(""), fd);
		return (tmp->next->content);
	}
	tmp = swap;
	swap->next = ft_lstnew(ft_strdup(""), fd);
	swap->next->next = tmp;
	return (swap->next->content);
}

static int		check_residual(char **line, t_list **residual, int fd)
{
	char		*pos;
	void		*str_residual;

	str_residual = (ft_get_residual(residual, fd));
	pos = ft_strchr((char *)str_residual, '\n');
	if (!pos)
	{
		*line = ft_strdup((char *)str_residual);
		return (1);
	}
	*pos = '\0';
	*line = ft_strdup((char *)str_residual);
	ft_strlcpy((char *)str_residual, pos + 1, -1);
	return (0);
}

void			set_residual(int fd, t_list *residual, char *tmp)
{
	while (residual->fd != fd)
		residual = residual->next;
	free(residual->content);
	residual->content = ft_strdup(tmp);
}

int				get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	static t_list	*residuals;
	char			*tmp;
	int				r;
	int				flag;

	if ((flag = check_residual(line, &residuals, fd)) == 0)
		return (1);
	while (flag && (r = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[r] = '\0';
		if ((tmp = ft_strchr(buffer, '\n')) && flag--)
		{
			*tmp++ = '\0';
			set_residual(fd, residuals, tmp);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	if (r == 0)
	{
		set_residual(fd, residuals, ft_strdup(""));
	}
	return ((r > 0) ? 1 : r);
}
