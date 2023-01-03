/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_blur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:03:36 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/03 13:11:21 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static void	normalise_color(t_frame_buffer *fb, int count)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			fb->motion_calc[y * WIN_W + x].s_rgb.r /= count;
			fb->motion_calc[y * WIN_W + x].s_rgb.g /= count;
			fb->motion_calc[y * WIN_W + x].s_rgb.b /= count;
			x++;
		}
		y++;
	}
}

static void	color_to_data(t_frame_buffer *fb)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			fb->data[y * WIN_W + x]
				= color_to_int(fb->motion_calc[y * WIN_W + x]);
			x++;
		}
		y++;
	}
}

static void	add_to_color_buffer(t_frame_buffer *fb, int times)
{
	t_color	color;
	int		y;
	int		x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = int_to_color(fb->data[y * WIN_W + x]);
			fb->motion_calc[y * WIN_W + x].s_rgb.r
				+= ((color.s_rgb.r / 255) * times);
			fb->motion_calc[y * WIN_W + x].s_rgb.g
				+= ((color.s_rgb.g / 255) * times);
			fb->motion_calc[y * WIN_W + x].s_rgb.b
				+= ((color.s_rgb.b / 255) * times);
			x++;
		}
		y++;
	}
}

void	create_motion_blur(t_main *main)
{
	int		frame_count;

	frame_count = 0;
	add_to_color_buffer(&main->sdl.frame_buffer, 20);
	while (motion_set_all(main) > 0)
	{
		main->scene.cam.coi_transform
			= coi_transform(&main->scene.cam, main->scene.cam.transform);
		main->settings.ant_al = 1;
		draw_frame(main);
		edge_detection(&main->sdl.frame_buffer, main->settings);
		main->settings.ant_al = main->settings.orig_ant_al;
		draw_frame(main);
		add_to_color_buffer(&main->sdl.frame_buffer, 1);
		frame_count++;
	}
	normalise_color(&main->sdl.frame_buffer, frame_count + 20);
	color_to_data(&main->sdl.frame_buffer);
	edge_detection(&main->sdl.frame_buffer, main->settings);
}
