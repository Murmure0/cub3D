/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:18:49 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/12 11:26:11 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_file	file;
	t_mlx	mlx;

	if (parse_file(&file, ac, av))
		return (1);
	if (launch_mlx(&mlx, &file))
		return (1);
	mlx_loop(mlx.init_ptr);
	system("leaks cub3d");
	return (0);
}
