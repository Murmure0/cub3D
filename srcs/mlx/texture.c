/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:30:36 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/09 13:49:02 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_texel_color(t_txt *txt, int x, int y, int dir)
{
	int	color;
	char *dst;

	dst = txt[dir].txt_adr + (y * txt->len + x * ((txt[dir].bpp)/8));
	color = (unsigned int)dst;
	return (color);
}

