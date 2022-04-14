/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:22:05 by cwastche          #+#    #+#             */
/*   Updated: 2022/02/04 09:19:39 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/so_long.h"

static char	*map_gnl(int fd)
{
	char	*ret;
	char	*tmp;
	char	*buff;

	ret = get_next_line(fd);
	while (1)
	{
		tmp = ret;
		buff = get_next_line(fd);
		if (!buff)
			break ;
		else
			ret = ft_strjoin(tmp, buff);
		free(tmp);
		free(buff);
	}
	return (ret);
}

static int	extension_check(char *map_path)
{
	char	*ext;
	int		ret;

	ext = ft_substr(map_path, ft_strlen(map_path) - 4, 4);
	//ADD MALLOC CHECK FOR EXT
	if (ft_strncmp(ext, ".cub", 4))
		ret = 1;
	else
		ret = 0;
	free(ext);
	return (ret);
}

char	*map_read(char *map_path)
{
	int		fd;
	char	*map;

	if (!map_path)
		error("No map file received.", NULL);
	if (extension_check(map_path))
		error("Wrong file extension used for chosen map file.", NULL);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error("An error occured with the \"open\" function", NULL);
	map = map_gnl(fd);
	if (close(fd) == -1)
	{
		free(map);
		error("An error occured with the \"close\" function", NULL);
	}
	return (map);
}
