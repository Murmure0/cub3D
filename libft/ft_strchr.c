/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:41:18 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/04 10:19:39 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;
	char	*str;

	str = (char *)s;
	d = (char)c;
	while (*str)
	{
		if (d == *str)
			return (str);
		str++;
	}
	if (c == 0)
		return (str);
	return (NULL);
}
