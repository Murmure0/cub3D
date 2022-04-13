/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:43:34 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/04 10:22:25 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	cpy = malloc((ft_strlen(s1) + 1));
	i = -1;
	if (!cpy)
		return (NULL);
	while (s1[++i])
		cpy[i] = s1[i];
	cpy[i] = 0;
	return (cpy);
}
