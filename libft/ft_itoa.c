/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:39:49 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/01 14:26:57 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int nb)
{
	int				i;
	unsigned int	n;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		n = -nb;
	else
		n = nb;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				len;
	char			*str;

	len = ft_len(n);
	if (n < 0)
	{
		len++;
		nb = -n;
	}
	else
		nb = n;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = 0;
	str[len - 1] = '0';
	if (n < 0)
		str[0] = '-';
	while (nb)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
