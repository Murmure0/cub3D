/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:28:22 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/16 14:39:23 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	fill_line(char	**str, int max_len)
{
	char	*tmp;
	char	*fill;
	int		i;
	int		len;

	len = ft_strlen(*str);
	fill = malloc(sizeof(char) * (max_len - len + 1));
	if (!fill)
		return (write(2, "Error\nMalloc failed.\n", 21), 1);
	tmp = ft_strdup(*str); //not necessary
	if (!tmp)
		return (free(fill), write(2, "Error\nMalloc failed.\n", 21), 1);
	i = -1;
	while (++i < max_len - len)
		fill[i] = '1';
	fill[i] = 0;
	free(*str);
	*str = ft_strjoin(tmp, fill);
	free(tmp);
	free(fill);
	if (!(*str))
		return (write(2, "Error\nMalloc failed.\n", 21), 1);
	return (0);
}

int	fill_map(char **scene)
{
	int	i;
	int	len;
	int	max_len;

	max_len = 0;
	i = -1;
	while (scene[++i])
	{
		len = ft_strlen(scene[i]);
		if (len > max_len)
			max_len = len;
	}
	i = -1;
	while (scene[++i])
	{
		len = ft_strlen(scene[i]);
		if (len < max_len)
		{
			if (fill_line(&scene[i], max_len))
				return (1);
		}
	}
	return (0);
}

char	*trim(char *str)
{
	char	*cpy;
	size_t	len;
	size_t	i;
	size_t	j;

	if (str == NULL)
		return (NULL);
	j = 0;
	while (str[j] && is_space(str[j]))
		j++;
	len = ft_strlen(str);
	while (is_space(str[len - 1]) && len > j)
		len--;
	cpy = malloc(sizeof(*str) * (len - j + 1));
	if (!cpy)
		return (cpy);
	i = 0;
	while (j < len)
		cpy[i++] = str[j++];
	cpy[i] = 0;
	return (cpy);
}
