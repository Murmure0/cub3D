/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:33:35 by cwastche          #+#    #+#             */
/*   Updated: 2021/07/28 12:35:46 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	size_t	len;
	size_t	i;
	size_t	j;

	if (s1 == NULL || set == NULL)
		return (NULL);
	j = 0;
	while (s1[j] && ft_isset(s1[j], set))
		j++;
	len = ft_strlen(s1);
	while (ft_isset(s1[len - 1], set) && len > j)
		len--;
	cpy = malloc(sizeof(*s1) * (len - j + 1));
	if (!cpy)
		return (cpy);
	i = 0;
	while (j < len)
		cpy[i++] = s1[j++];
	cpy[i] = 0;
	return (cpy);
}
