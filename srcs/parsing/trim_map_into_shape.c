#include "cub.h"

static int	fill_line(char	**str, int max_len)
{
	char	*tmp;
	char	*fill;
	int		i;
	int		len;

	len = ft_strlen(*str);
	fill = malloc(sizeof(char) * (max_len - len + 1));
	if (!fill)
		return (write(2, "Error\nMalloc failed.\n", 21), 1);
	tmp = ft_strdup(*str);
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

//------------------------------
/*

static int	trim_start(char **map)
{
	int	i;
	int	j;
	int	ret;

	ret = INT_MAX;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
				if (j - 1 < ret)
					ret = j - 1;
		}
	}
	return (ret);
}

static int	trim_end(char **map)
{
	int	i;
	int	j;
	int	ret;
	int	len;

	ret = INT_MAX;
	i = -1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		j = len;
		j--;
		while (map[i][j] && j > 0)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
				if (len - j - 2 < ret)
					ret = len - j - 2;
			j--;
		}
	}
	return (ret);
}

char	*trim_line(int start, int end, char *line)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(line - start - end);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (write(2, "Error\nMalloc failed\n", 19), NULL);
	i = -1;
	while (++i < len)
		ret[i] = line[i + start];
	ret[i] = 0;
	free(line);
	return (ret);
}

int	trim_map_into_shape(t_file *file)
{
	int		i;
	int		start;
	int		end;
	char	**trimmed_map;

	trimmed_map = malloc(sizeof(char *) * (arraylen(file->scene) + 1));
	start = trim_start(file->scene);
	end = trim_end(file->scene);
	i = -1;
	while (file->scene[++i])
	{
		trimmed_map[i] = trim_line(start, end, file->scene[i]);
		if (!trimmed_map[i])
			return (1);
	}
	trimmed_map[i] = 0;
	file->scene = trimmed_map;
	return (0);
}
*/