/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:05:33 by cwastche          #+#    #+#             */
/*   Updated: 2021/07/17 16:43:36 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*cpy;
	unsigned int	len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	cpy = malloc(len + 1);
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (len > i)
	{
		cpy[i] = f(i, s[i]);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
