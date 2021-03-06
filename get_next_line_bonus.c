/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:28:42 by Kwillum           #+#    #+#             */
/*   Updated: 2020/05/12 18:58:40 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*ft_get_residual(t_list **residual, int fd)
{
	t_list	*tmp;

	if (!(*residual))
	{
		*residual = ft_lstnew(ft_strdup(""), fd);
		if (!(*residual) || ((*residual)->content == NULL))
			return (NULL);
		return ((*residual)->content);
	}
	tmp = *residual;
	while ((tmp->fd != fd) && (tmp->next))
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp->content);
	tmp->next = ft_lstnew(ft_strdup(""), fd);
	if (!(tmp->next) || (tmp->next->content == NULL))
		return (NULL);
	return (tmp->next->content);
}

static int		check_residual(char **line, t_list **residual, int fd)
{
	char		*pos;
	void		*str_residual;
	char		*tmp;

	str_residual = ft_get_residual(residual, fd);
	if (!str_residual || !line)
		return (-1);
	pos = ft_strchr((char *)str_residual, '\n');
	if (!pos)
	{
		*line = ft_strdup((char *)str_residual);
		if (*line)
			return (1);
		return (-1);
	}
	*pos++ = '\0';
	*line = ft_strdup((char *)str_residual);
	if (*line == NULL)
		return (-1);
	tmp = (char *)str_residual;
	while (*pos)
		*tmp++ = *pos++;
	*tmp = '\0';
	return (0);
}

static int		free_memory(t_list **residuals, int fd)
{
	t_list	*tmp;
	t_list	*residual;

	residual = *residuals;
	if (!residual)
		return (-1);
	tmp = residual;
	while ((residual->fd != fd) && (residual->next))
	{
		tmp = residual;
		residual = residual->next;
	}
	if (residual->fd != fd)
		return (-1);
	free(residual->content);
	if (tmp == residual)
		*residuals = residual->next;
	else
		tmp->next = residual->next;
	free(residual);
	return (-1);
}

static int		set_residual(int fd, t_list **residuals, char *tmp)
{
	t_list	*residual;

	residual = *residuals;
	if (!residual)
		return (-1);
	while (residual->fd != fd)
		residual = residual->next;
	free(residual->content);
	if (!tmp)
		residual->content = ft_strdup("");
	else
		residual->content = ft_strdup(tmp);
	if (residual->content == NULL)
	{
		free_memory(residuals, fd);
		return (-1);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	static t_list	*residuals;
	char			*tmp;
	int				r;
	int				flag;

	if ((flag = check_residual(line, &residuals, fd)) <= 0)
		return (flag == 0 ? 1 : free_memory(&residuals, fd));
	while (flag && (r = read(fd, buffer, BUFFER_SIZE)) > 0 && *line)
	{
		buffer[r] = '\0';
		if ((tmp = ft_strchr(buffer, '\n')) && flag--)
		{
			*tmp++ = '\0';
			r = set_residual(fd, &residuals, tmp);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	if (!(*line))
		r = -1;
	if (r == 0 || r == -1)
		free_memory(&residuals, fd);
	return ((r > 0) ? 1 : r);
}
