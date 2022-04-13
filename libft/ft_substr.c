/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:36:39 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/04 11:39:53 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	cpy = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!cpy)
		return (NULL);
	while (i < len && &s[start + i])
	{
		cpy[i] = (char)s[start + i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
