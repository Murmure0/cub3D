/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:46:53 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/18 10:19:53 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_color(char **tmp)
{
	int		i;
	int		j;

	i = -1;
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			if (!ft_isdigit(tmp[i][j]) && tmp[i][j] != '\n')
			{
				free_tab(tmp);
				return (write_ret("Error\nDigits only\n"));
			}
		}
		if (ft_atoi(tmp[i]) < 0 || ft_atoi(tmp[i]) > 255)
		{
			free_tab(tmp);
			return (write_ret("Error\nWrong color value\n"));
		}
	}
	return (0);
}

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
		if (len == 0)
			return (printf("TRIM_SPACES 84\n"), 1);
		tmp = malloc(sizeof(char) * (len - j + 1) + 1);
		if (!tmp)
			return (write_ret("Error\nMalloc failed\n"));
		k = 0;
		while (j < len)
			tmp[k++] = str[i][j++];
		tmp[k] = 0;
		free(str[i]);
		str[i] = tmp;
	}
	return (0);
}
