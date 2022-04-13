/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:41:36 by cwastche          #+#    #+#             */
/*   Updated: 2021/07/06 17:04:34 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (*src && i + 1 < dstsize)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	if (i < dstsize)
		dst[i] = 0;
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}
