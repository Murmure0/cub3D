/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:42:24 by cwastche          #+#    #+#             */
/*   Updated: 2021/07/17 18:05:40 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	d;
	char	*str;

	str = (char *)s;
	d = (char)c;
	tmp = NULL;
	while (*str)
	{
		if (d == *str)
			tmp = str;
		str++;
	}
	if (c == 0)
		return (str);
	return (tmp);
}
