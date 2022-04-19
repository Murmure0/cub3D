int check_first_line(char **wall)
{
	int j;
	int	len;

	j = -1;
	len = ft_strlen(wall[1]);
	while (wall[0][++j])
	{
		if (wall[0][j] == ' ')
		{
			if (wall[0][j + 1] != '1' && wall[0][j + 1] != ' '
				&& wall[0][j + 1] != '\n' && wall[0][j + 1] != EOF)
				return (1);
			if (len >= j)
				if (wall[1][j] != '1' && wall[1][j] != ' '
					&& wall[1][j] != '\n' && wall[1][j] != EOF)
					return (1);			
		}
		else if (wall[0][j] != '1')
			return (1);
	}
	return (0);
}

int check_last_line(char **wall, int i)
{
	int j;

	j = -1;
	while (wall[i][++j])
	{
		if (wall[i][j] == ' ')
		{
			if ((wall[i][j + 1] != '1' && wall[i][j + 1] != ' ')
				|| (wall[i - 1][j] != '1' && wall[i - 1][j] != ' '))
				return (1);
		}
		else if (wall[i][j] != '1')
			return (1);
	}
	return (0);
}