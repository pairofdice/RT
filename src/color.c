/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:32:44 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 24 | g << 16 | b << 8);
}

unsigned int	color_to_int(t_color color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)(float_clamp(color.s_rgb.r, 0.0, 1.0) * 255);
	g = (unsigned char)(float_clamp(color.s_rgb.g, 0.0, 1.0) * 255);
	b = (unsigned char)(float_clamp(color.s_rgb.b, 0.0, 1.0) * 255);
	return (r << 24 | g << 16 | b << 8);
}

t_color	int_to_color(unsigned int rgba)
{
	t_color	color;

	color.s_rgb.b = (rgba >> 8) % 256;
	color.s_rgb.g = (rgba >> 16) % 256;
	color.s_rgb.r = (rgba >> 24) % 256;
	color.s_xyzw.w = 0;
	return (color);
}

t_color	color_multiply(t_color a, t_color b)
{
	t_color	color;

	color.s_rgb.r = a.s_rgb.r * b.s_rgb.r;
	color.s_rgb.g = a.s_rgb.g * b.s_rgb.g;
	color.s_rgb.b = a.s_rgb.b * b.s_rgb.b;
	return (color);
}

t_color	color_new(double r, double g, double b)
{
	t_color	color;

	color.s_rgb.r = r;
	color.s_rgb.g = g;
	color.s_rgb.b = b;
	color.s_xyzw.w = 0;
	return (color);
}
