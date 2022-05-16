/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:46:53 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/16 15:55:15 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_param_chains(t_file *f, t_list *head)
{
	t_list	*tmp;

	while (f->map != head)
	{
		tmp = f->map->next;
		ft_lstdelone(f->map, free);
		f->map = tmp;
	}
}

void	param_count_init(t_p_nb *p_nb)
{
	p_nb->c = 0;
	p_nb->f = 0;
	p_nb->no = 0;
	p_nb->so = 0;
	p_nb->we = 0;
	p_nb->ea = 0;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	trim_spaces(char **str)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		j = parse_spaces(str[i]);
		len = ft_strlen(str[i]);
		while (len && is_space(str[i][len - 1]))
			len--;
		tmp = malloc(sizeof(char) * (len - j + 1));
		if (!tmp)
			return (write(2, "Error\nMalloc failed\n", 20), 1);
		k = 0;
		while (j < len)
			tmp[k++] = str[i][j++];
		tmp[k] = 0;
		free(str[i]);
		str[i] = tmp;
	}
	return (0);
}
