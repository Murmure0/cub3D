/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:53:40 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/28 22:35:03 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	d;

	if (!s)
		return (NULL);
	str = (char *)s;
	d = (char)c;
	while (*str)
	{
		if (*str == d)
			return (str);
		str++;
	}
	if (c == 0)
		return (str);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	cpy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy)
		return (NULL);
	i = -1;
	while (s1[++i])
		cpy[i] = s1[i];
	cpy[i] = 0;
	return (cpy);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*cpy;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	cpy = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (*s1)
		cpy[i++] = *s1++;
	while (*s2)
		cpy[i++] = *s2++;
	cpy[i] = 0;
	return (cpy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len && &s[start + i])
	{
		cpy[i] = (char)s[start + i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
