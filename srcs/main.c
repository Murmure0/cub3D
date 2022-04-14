/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:18:49 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/14 17:45:30 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main (int ac, char **av)
{
	t_file file;
	t_mlx mlx;

	if (parse_file(&file, ac, av))
		return(1);
	if(init_mlx(&mlx, &file))
		return (1);
	mlx_loop(mlx.init_ptr);
	printf("coucou\n");
	return (0);
}