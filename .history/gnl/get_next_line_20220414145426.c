/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:52:28 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/28 22:42:04 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_all(int read_ret, char **s, int fd)
{
	if (read_ret < 0)
		free(s[fd]);
	return (NULL);
}

static char	*save_line(int fd, char **s, int i)
{
	char	*tmp;
	char	*line;

	if (s[fd][i] == '\n')
		i++;
//	line = ft_substr(s[fd], 0, i + 1);
	line = ft_substr(s[fd], 0, i); //Does not return /n from read line
	tmp = ft_strdup(&s[fd][i + 1]);
	free(s[fd]);
	s[fd] = 0;
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	if (*tmp)
		s[fd] = ft_strdup(tmp);
	free(tmp);
	return (line);
}

static char	*return_line(int fd, char **s)
{
	size_t	i;
	char	*line;

	i = 0;
	while ((s[fd][i] != '\n') && s[fd][i])
		i++;
	if (!s[fd][i])
	{
		line = ft_strdup(s[fd]);
		free(s[fd]);
		s[fd] = 0;
	}
	else
		line = save_line(fd, s, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s[FD_MAX];
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		read_ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	read_ret = read(fd, buff, BUFFER_SIZE);
	while (read_ret > 0)
	{
		buff[read_ret] = 0;
		if (!s[fd])
			s[fd] = ft_strdup("");
		tmp = ft_strdup(s[fd]);
		free(s[fd]);
		s[fd] = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(s[fd], '\n'))
			break ;
		read_ret = read(fd, buff, BUFFER_SIZE);
	}
	if (read_ret < 0 || (read_ret == 0 && !s[fd]))
		return (free_all(read_ret, s, fd));
	return (return_line(fd, s));
}
