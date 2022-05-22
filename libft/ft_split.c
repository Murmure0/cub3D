/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:09:31 by cwastche          #+#    #+#             */
/*   Updated: 2021/07/18 10:56:50 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_split(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (*s)
	{
		if (word == 0 && *s != c)
		{
			i++;
			word = 1;
		}
		else if (word == 1 && *s == c)
			word = 0;
		s++;
	}
	return (i);
}

static void	*ft_free_split(char **tab, int i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static void	init_to_null(char **tab, int i)
{
	while (i)
	{
		tab[i] = NULL;
		i--;
	}
	tab = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	init_to_null(tab, words);
	i = 0;
	if (!tab)
		return (NULL);
	while (words--)
	{
		while (*s == c && *s != 0)
			s++;
		tab[i] = ft_substr(s, 0, ft_strlen_split(s, c));
		if (!tab[i])
			return (ft_free_split(tab, i));
		s += ft_strlen_split(s, c);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
