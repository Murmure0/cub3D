/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:58 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/13 13:17:47 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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

void	error(char *msg, t_data *var) //copie de so_long, exit ?
{
	if (var->map)
		map_free(var->map);
	printf("Error.\n");
	printf("%s\n", msg);
	exit(EXIT_SUCCESS);
}

static int	verify_extension(char *path_to_map)
{
	char	*ext;
	int		ret;

	ext = ft_substr(path_to_map, ft_strlen(path_to_map) - 4, 4);
	//ADD MALLOC CHECK FOR EXT
	if (ft_strncmp(ext, ".cub", 4))
		ret = 1;
	else
		ret = 0;
	free(ext);
	return (ret);
}

void	verify_input(t_file *file, char *path_to_map)
{
	if (verify_extension(path_to_map))
		error("Wrong file extension used for chosen map file.", NULL);
}

int parse_file(t_file *file, int ac, char **av)
{
	(void)file;
	(void)ac;
	(void)av;
	if (ac != 2)
		return (printf("Wrong number of arguments\n"), 1);
	verify_input(file, av[1]);
	return (0);
}