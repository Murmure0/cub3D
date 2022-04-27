/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:15:53 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/15 18:52:33 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_chars_used(t_list *map)
{
	t_list	*tmp;
	char	*str;
	int		i;
	int		player_count;

	tmp = map;
	player_count = 0;
	while (tmp)
	{
		i = -1;
		str = (char *)tmp->content;
		while (str[++i])
		{
			if (str[i] == 'N' || str[i] == 'S'
				|| str[i] == 'E' || str[i] == 'W')
				player_count++;
			if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S'
				&& str[i] != 'E' && str[i] != 'W'
				&& !is_space(str[i]) && str[i] != '\n')
				return (write(2, "Error\nForbidden char in map\n", 29), 1);
		}
		tmp = tmp->next;
	}
	if (player_count > 1)
		return (write(2, "Error\nMore than 1 player detected\n", 34), 1);
	else if (player_count < 1)
		return (write(2, "Error\nMissing player\n", 21), 1);
	return (0);
}

static int	check_map(t_file *file)
{
	if (ft_lstsize(file->map) < 3)
		return (write(2, "Error\nMap too small\n", 21), 1);
	if (check_chars_used(file->map))
		return (1);
	if (not_walled_in(file))
		return (1);
	return (0);
}

static int	read_file(int fd, t_file *file)
{
	t_list	*chain;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (write(2, "Error\nEmpty file.\n", 18), 1);
	file->map = ft_lstnew(line);
	if (!file->map)
		return (write(2, "Error\nMalloc failed.\n", 22), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		chain = ft_lstnew(line);
		if (!chain)
		{
			write(2, "Error\nMalloc failed.", 22);
			return (ft_lstclear(&file->map, free), 1);
		}
		ft_lstadd_back(&file->map, chain);
	}
	return (0);
}

static int	check_file(int ac, char **av)
{
	if (ac != 2)
		return (write(2, "Error\nArgument invalid.\n", 24), 1);
	if (ft_strncmp(".cub", &av[1][ft_strlen(av[1]) - 4], 4))
		return (write(2, "Error\nWrong extension file.\n", 28), 1);
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

int	check_for_colors(t_list *head)
{
	int		i;
	int		ret;
	char	*str;
	char	**tmp;

	i = 0;
	ret = 0;
	// str = head->content;
	// i += parse_spaces(str);
	str = trim(head->content);
	printf("str = %s\n", str);
	if (str[i] == 'C' || str[i] == 'F')
	{
		// tmp = ft_split(str + i, ',');
		tmp = ft_split(str, ',');
		// trim_spaces(tmp);
		i = 0;
		while (tmp[i])
			i++;
		printf("i = %d\n", i);
		if (i < 3)
			ret = 1;
		while (*tmp)
			free(*tmp++);
		// free(tmp);
	}
	return (ret);
}

void	param_join(t_file *file)
{
	t_list	*tmp;
	t_list	*head;
	char	*str;
	char	*cpy;
	int		i;

	tmp = file->map;
	while (tmp)
	{
		i = 0;
		str = tmp->content;
		i += parse_spaces(str);
		if (str[i] == '\n')
		{
			tmp = tmp->next;
			continue ;
		}
		else if (((str[i] == '0' || str[i] == '1') && !check_for_colors(head)) || (str[i] == 'N' && str[i + 1] != 'O') 
			|| (str[i] == 'S' && str[i + 1] != 'O') || (str[i] == 'E' && str[i + 1] != 'A') 
			|| (str[i] == 'W' && str[i + 1] != 'E'))
		{
			head = tmp;
			tmp = tmp->next;
		}
		else if (str[i] == 'C'|| str[i] == 'F' || (str[i] == 'N' && str[i + 1] == 'O')
			|| (str[i] == 'S' && str[i + 1] == 'O') || (str[i] == 'E' && str[i + 1] == 'A')
			|| (str[i] == 'W' && str[i + 1] == 'E'))
		{
			head = tmp;
			tmp = tmp->next;
		}
		else
		{
			cpy = ft_strjoin(head->content, tmp->content);
			free(head->content);
			head->content = cpy;
			head->next = tmp->next; // if \n in between lost memory
			ft_lstdelone(tmp, free);
			tmp = head->next;
			// printf("LAST HEAD: %s\n", head->content);
		}
	}
}

void	print_map(t_list *map) //TODEL
{
	t_list *tmp;

	tmp = map;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	parse_file(t_file *file, int ac, char **av)
{
	int	fd;

	if (check_file(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpen"), 1);
	if (read_file(fd, file))
		return (1);
	param_join(file);
	print_map(file->map); //TODEL
	if (check_params(file))
		return (1);
	if (check_map(file))
		return (1);
	return (0);
}
