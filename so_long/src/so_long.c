/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:22:09 by cwastche          #+#    #+#             */
/*   Updated: 2022/02/04 11:06:29 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/so_long.h"	

static int	key_hook(int keycode, t_data *var)
{
	if (keycode == 119)
		move_up(var);
	else if (keycode == 100)
		move_right(var);
	else if (keycode == 115)
		move_down(var);
	else if (keycode == 97)
		move_left(var);
	else if (keycode == 65307)
		close_win(var);
}

int	main(int ac, char **av)
{
	char	*line;
	t_data	var;

	if (ac != 2)
		return (1);
	var.moves = 1;
	line = map_read(av[1]);
	var.map = ft_split(line, '\n');
	if (!var.map)
		return (printf("Error.\nGiven map is empty.\n"));
	free(line);
	map_check(&var);
	map_size(&var);
	var.mlx = mlx_init();
	if (var.mlx == NULL)
		return (error_win(&var, 1));
	var.win = mlx_new_window(var.mlx, var.map_w, var.map_h, "So_long");
	if (var.win == NULL)
		return (error_win(&var, 2));
	mlx_key_hook(var.win, key_hook, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_hook(var.win, 12, 1L << 15, generate_map, &var);
	mlx_loop(var.mlx);
	map_free(var.map);
	return (0);
}
