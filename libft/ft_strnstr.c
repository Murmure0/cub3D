/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:42:16 by cwastche          #+#    #+#             */
/*   Updated: 2021/07/17 18:37:20 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*tmp;
	char	*needle_cpy;
	size_t	len_needle;

	if (!*needle)
		return ((char *)haystack);
	len_needle = ft_strlen(needle);
	if (!ft_strlen(haystack) || len < len_needle)
		return (0);
	len -= len_needle - 1;
	while (*haystack && len--)
	{
		tmp = (char *)haystack;
		needle_cpy = (char *)needle;
		while (*tmp == *needle_cpy && *needle_cpy)
		{
			tmp++;
			needle_cpy++;
		}
		if (*needle_cpy == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (0);
}
