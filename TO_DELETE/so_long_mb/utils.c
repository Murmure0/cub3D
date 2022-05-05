/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:17:41 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/07 16:28:53 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	unsigned int	nb;

	nb = n;
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}

static int	ft_count(int n)
{
	unsigned int	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned char	*str;
	int				j;
	unsigned int	nb;

	nb = (unsigned int)n;
	j = ft_count(n);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	*(str + j) = '\0';
	while (j-- > 0)
	{	
		*(str + j) = (nb % 10) + '0';
		nb /= 10;
	}
	return ((char *)str);
}
