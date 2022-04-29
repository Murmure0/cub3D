#include "cub.h"

int	is_space(char c)
{
	if (c == 9 || (c >= 11 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	check_left_wall(char *str)
{
	int	wall;
	int i;

	wall = 0;
	i = parse_spaces(str);
	while (str[i])
	{
		if (str[i] != '1' && wall == 0)
			return (1);
		else
			wall = 1;
		i++;
	}
	return (0);
}

int	check_right_wall(char *str)
{
	int	wall;
	int i;

	i = ft_strlen(str);
	wall = 0;
	while (--i >= 0)
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] != '1' && wall == 0)
			return (1);
		else
			wall = 1;
	}
	return (0);
}