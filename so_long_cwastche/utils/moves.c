/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:22:19 by cwastche          #+#    #+#             */
/*   Updated: 2022/02/02 22:55:46 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/so_long.h"

int	move_up(t_data *var)
{
	int		x;
	int		y;
	char	tmp;

	x = var->player_x;
	y = var->player_y;
	if (var->map[y - 1][x] == '1' || (var->map[y - 1][x] == 'E' && var->c > 0))
		return (1);
	printf("Number of moves = %d\n", var->moves++);
	if (var->map[y - 1][x] == '0')
	{
		var->map[y][x] = '0';
		var->map[y - 1][x] = 'P';
	}
	if (var->map[y - 1][x] == 'C')
	{
		var->c -= 1;
		var->map[y - 1][x] = 'P';
		var->map[y][x] = '0';
	}
	if (var->map[y - 1][x] == 'E' && var->c == 0)
		close_win(var);
	generate_map(var);
}

int	move_down(t_data *var)
{
	int		x;
	int		y;
	char	tmp;

	x = var->player_x;
	y = var->player_y;
	if (var->map[y + 1][x] == '1' || (var->map[y + 1][x] == 'E' && var->c > 0))
		return (1);
	printf("Number of moves = %d\n", var->moves++);
	if (var->map[y + 1][x] == '0')
	{
		var->map[y][x] = '0';
		var->map[y + 1][x] = 'P';
	}
	if (var->map[y + 1][x] == 'C')
	{
		var->c -= 1;
		var->map[y + 1][x] = 'P';
		var->map[y][x] = '0';
	}
	if (var->map[y + 1][x] == 'E' && var->c == 0)
		close_win(var);
	generate_map(var);
}

int	move_left(t_data *var)
{
	int		x;
	int		y;
	char	tmp;

	x = var->player_x;
	y = var->player_y;
	if (var->map[y][x - 1] == '1' || (var->map[y][x - 1] == 'E' && var->c > 0))
		return (1);
	printf("Number of moves = %d\n", var->moves++);
	if (var->map[y][x - 1] == '0')
	{
		var->map[y][x] = '0';
		var->map[y][x - 1] = 'P';
	}
	if (var->map[y][x - 1] == 'C')
	{
		var->c -= 1;
		var->map[y][x - 1] = 'P';
		var->map[y][x] = '0';
	}
	if (var->map[y][x - 1] == 'E' && var->c == 0)
		close_win(var);
	generate_map(var);
}

int	move_right(t_data *var)
{
	int		x;
	int		y;
	char	tmp;

	x = var->player_x;
	y = var->player_y;
	if (var->map[y][x + 1] == '1' || (var->map[y][x + 1] == 'E' && var->c > 0))
		return (1);
	printf("Number of moves = %d\n", var->moves++);
	if (var->map[y][x + 1] == '0')
	{
		var->map[y][x] = '0';
		var->map[y][x + 1] = 'P';
	}
	if (var->map[y][x + 1] == 'C')
	{
		var->c -= 1;
		var->map[y][x + 1] = 'P';
		var->map[y][x] = '0';
	}
	if (var->map[y][x + 1] == 'E' && var->c == 0)
		close_win(var);
	generate_map(var);
}
