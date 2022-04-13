/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:18:49 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/13 13:17:07 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main (int ac, char **av)
{
	t_file file;

	if (parse_file(&file, ac, av))
		return(1);
	printf("coucou");
	return (0);
}