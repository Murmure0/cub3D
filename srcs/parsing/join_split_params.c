#include "cub.h"

static char	*trim(char *str)
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

static int	check_for_colors(t_list *head)
{
	int		i;
	int		ret;
	char	*str;
	char	**tmp;

	i = 0;
	ret = 0;
	str = trim(head->content);
	if (str[i] == 'C' || str[i] == 'F')
	{
		tmp = ft_split(str, ',');
		i = 0;
		while (tmp[i])
			i++;
		if (i < 3)
			ret = 1;
		while (*tmp)
			free(*tmp++);
	}
	return (ret);
}

static int	map_id_found(t_list **head, int i, t_list *tmp)
{
	int		ret;
	char	*str;

	str = tmp->content;
	ret = 0;
	if ((str[i] == '0' || str[i] == '1') && !check_for_colors(head))
		ret = 1;
	else if (str[i] == 'N' && str[i + 1] != 'O')
		ret = 1;
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ret = 1;
	else if (str[i] == 'E' && str[i + 1] != 'A')
		ret = 1;
	else if (str[i] == 'W' && str[i + 1] != 'E')
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

void	join_split_params(t_file *file)
{
	t_list	*tmp;
	t_list	*head;
	char	*cpy;
	char	*str;

	tmp = file->map;
	while (tmp)
	{
		str = tmp->content;
		if (str[parse_spaces(str)] == '\n')
			tmp = tmp->next;
		else if (map_id_found(&head, parse_spaces(str), tmp))
			tmp = tmp->next;	
		else if (param_id_found(&head, parse_spaces(str), tmp))
			tmp = tmp->next;
		else
		{
			cpy = ft_strjoin(head->content, tmp->content);
			free(head->content);
			head->content = cpy;
			head->next = tmp->next;
			ft_lstdelone(tmp, free);
			tmp = head->next;
		}
	}
}
