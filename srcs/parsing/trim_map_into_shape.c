#include "cub.h"

//LOGIC DOES NOT WORK, IN STANDBY ATM
//CODE WILL NOT WORK WITH MAPS THAT LOOK LIKE
//       1111
//  1111100N1
//  111111111

static int	trim_start(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '0' || s[i] == 'N' || s[i] == 'W'
			|| s[i] == 'E' || s[i] == 'S');
			return (i - 1);
	}
	return (0);
}

static int	trim_end()
{

}

int	trim_map_into_shape(t_file *file)
{
	int		i;
	int		start;
	int		end;
	int		new_len;
	char	**trimmed_map;

	i = -1;
	while (file->scene[++i])
	{
		start = trim_start(file->scene[i]);
		end = trim_end(file->scene[i]);
		j = 0;
		new_len = ft_strlen(file->scene[i] - start - end;
		trimmed_map[i] = malloc(sizeof(char) * (new_len + 1))
		if (!trimmed_map[i])
			return (write(2, "Error\nMalloc failed\n", 19), 1);
		while (j < new_len)
			trimmed_map[i][j] = file->scene[i][j + start];
		trimmed_map[i][j] = 0;
		free(file->scene[i]);
	}
	file->scene = trimmed_map;
	return (0);
}