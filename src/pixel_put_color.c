/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:20:23 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/30 15:16:02 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

void	img_pixel_put(t_frame_buffer *fb, unsigned int x,
	unsigned int y, t_color color)
{
	char			*dst;
	unsigned int	color_int;

	color_int = rgb_to_int((unsigned int)color.x,
			(unsigned int)color.y,
			(unsigned int)color.z);
	dst = fb->data + (y * WIN_W + x) * 4;
	*(unsigned int *)dst = color_int;
}

unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	return (r << 24 | g << 16 | b << 8);
}
