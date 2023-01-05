/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:02:06 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/05 12:39:29 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	int_to_rgb(int color, t_color *rgb)
{
	rgb->s_rgb.r = (color) >> 24 & 255;
	rgb->s_rgb.g = (color) >> 16 & 255;
	rgb->s_rgb.b = (color) >> 8 & 255;
}

int	rgb_to_white(t_color *rgb)
{
	int	color;

	color = (((rgb->s_rgb.r * 0.4)
				+ (rgb->s_rgb.g * 0.3)
				+ (rgb->s_rgb.b * 0.3)));
	return (color << 24 | color << 16 | color << 8);
}

/*
**	test_pixel test the pixel if it haves edge in the image.
**	id adds every pixel around the test pixel (that are inside the image)
**	and return te diference.
*/

double	test_pixel(int *image, int i, int j)
{
	double	pixel;
	double	compare;
	int		count;

	count = 0;
	pixel = ((((image[(j * WIN_W) + i]) >> 24 & 255) / 255.0));
	compare = edge_detection_check(i - 1, j, &count, image);
	compare += edge_detection_check(i + 1, j, &count, image);
	compare += edge_detection_check(i - 1, j + 1, &count, image);
	compare += edge_detection_check(i, j + 1, &count, image);
	compare += edge_detection_check(i + 1, j + 1, &count, image);
	compare += edge_detection_check(i - 1, j - 1, &count, image);
	compare += edge_detection_check(i, j - 1, &count, image);
	compare += edge_detection_check(i + 1, j - 1, &count, image);
	pixel *= count;
	pixel -= compare;
	return (pixel);
}

/*
**	great_mask checks every pixel of the original photo what is turned to
**	black and whit image.
**	It checks the diference between test pixel and pixels around it
**	returned by test_pixel abow and if thediference is too big it marks it
**	down to fb->mask for creating filters and also for further
**	anti aliasing ptimisation.
**	scale is something that you can change in .xml file so it will be more
**	precice whit color changes.
*/

static void	great_mask(t_frame_buffer *fb, t_settings s)
{
	int		i;
	int		j;
	double	color;
	double	scale;

	scale = s.edge_detection_presission;
	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			fb->mask[(j * WIN_W) + i] = 0;
			color = test_pixel(fb->filter, i, j);
			if (color > scale || color < -scale)
				fb->mask[(j * WIN_W) + i] = 1;
			i++;
		}
		j++;
	}
}

void	edge_detection(t_frame_buffer *fb, t_settings s)
{
	t_color	rgb;
	int		color;
	int		i;
	int		j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			int_to_rgb(fb->data[((j * WIN_W) + i)], &rgb);
			color = rgb_to_white(&rgb);
			fb->filter[((j * WIN_W) + i++)] = color;
		}
		j++;
	}
	great_mask(fb, s);
}
