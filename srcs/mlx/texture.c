/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:30:36 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/10 14:44:42 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int	get_texel_color(t_txt *txt, int x, int y, int dir)
// {
// 	int	color;
// 	char *dst;

// 	dst = txt[dir].txt_adr + (y * txt->len + x * (txt[dir].bpp/8));
// 	printf("dir : %d \n", dir);
// 	color = *(unsigned int *)dst;
// 	return (color);
// }

int	get_texel_color(t_txt *txt, int x, int y)
{
	int	color;
	char *dst;

	dst = txt->txt_adr + (y * txt->len + x * (txt->bpp/8));
	color = *(unsigned int *)dst;
	return (color);
}

