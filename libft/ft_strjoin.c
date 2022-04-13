/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:13 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/04 10:19:30 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*cpy;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	cpy = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!cpy)
		return (NULL);
	while (*s1)
		cpy[i++] = *s1++;
	while (*s2)
		cpy[i++] = *s2++;
	cpy[i] = 0;
	return (cpy);
}
