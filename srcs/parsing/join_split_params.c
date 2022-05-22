/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_split_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:48:02 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/18 10:01:13 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_for_colors(t_list *head)
{
	int		i;
	int		ret;
	char	*str;
	char	**tmp;

	if (!head)
		return (0);
	ret = 0;
	str = trim(head->content);
	if (!str)
		return (-1);
	if (str[0] == 'C' || str[0] == 'F')
	{
		tmp = ft_split(str, ',');
		if (!tmp)
			return (free(str), -1);
		i = 0;
		while (tmp[i])
			i++;
		if (i < 3)
			ret = 1;
		free_tab(tmp);
	}
	free(str);
	return (ret);
}

static int	map_id_found(t_list **head, int i, t_list *tmp)
{
	int		ret;
	char	*str;
	int		colors;

	str = tmp->content;
	ret = 0;
	if ((str[i] == '0' || str[i] == '1'))
	{
		colors = check_for_colors(*head);
		if (colors == -1)
			return (-1);
		if (!colors)
			ret = 1;
	}
	else if ((str[i] == 'N' && str[i + 1] != 'O')
		|| (str[i] == 'S' && str[i + 1] != 'O')
		|| (str[i] == 'E' && str[i + 1] != 'A')
		|| (str[i] == 'W' && str[i + 1] != 'E'))
		ret = 1;
	if (ret)
		*head = tmp;
	return (ret);
}

static int	param_id_found(t_list **head, int i, t_list *tmp)
{
	int		ret;
	char	*str;

	str = tmp->content;
	ret = 0;
	if (str[i] == 'C' || str[i] == 'F')
		ret = 1;
	else if (str[i] == 'N' && str[i + 1] == 'O')
		ret = 1;
	else if (str[i] == 'S' && str[i + 1] == 'O')
		ret = 1;
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ret = 1;
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ret = 1;
	if (ret)
		*head = tmp;
	return (ret);
}

static int	join_lines(t_list *tmp, t_list *head)
{
	char	*cpy;

	if (!head)
		return (write_ret("Error\nRandom line found\n"));
	cpy = ft_strjoin(head->content, tmp->content);
	if (!cpy)
		return (write_ret("Error\nMalloc failed\n"));
	free(head->content);
	head->content = cpy;
	head->next = tmp->next;
	ft_lstdelone(tmp, free);
	return (0);
}

int	join_split_params(t_file *file, t_list *head)
{
	t_list	*tmp;
	int		ret;

	tmp = file->map;
	while (tmp)
	{
		if (((char *)tmp->content)[parse_spaces((char *)tmp->content)] == '\n')
		{
			tmp = tmp->next;
			continue ;
		}
		ret = map_id_found(&head, parse_spaces(tmp->content), tmp);
		if (ret == -1)
			return (write_ret("Error\nMalloc failedfesfsefsefesf\n"));
		if (ret)
			return (0);
		else if (param_id_found(&head, parse_spaces(tmp->content), tmp))
			tmp = tmp->next;
		else
			if (join_lines(tmp, head))
				return (1);
		tmp = head->next;
	}
	return (0);
}
