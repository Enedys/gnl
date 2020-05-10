/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 22:41:16 by Kwillum           #+#    #+#             */
/*   Updated: 2020/05/10 01:35:56 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <stdio.h>

typedef struct			s_list
{
	void				*content;
	int					fd;
	struct s_list		*next;
}						t_list;

int						get_next_line(int fd, char **line);
size_t					ft_strlen(const char *s);
size_t					ft_strlcpy(char *dest, const char *src, size_t n);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
void					print_list(t_list *lst);

#endif
