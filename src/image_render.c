/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:56:58 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/19 14:16:05 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static void	aa_help(t_anti_aliasing *aa, t_main *main, int pixel_x)
{
	aa->x = ((float)pixel_x + (aa->offset / 2) + (aa->offset * aa->i));
	initialize_ray(&main->ray, aa->x, aa->y, &main->scene.cam);
	aa->color = tuple_add(aa->color, color_at(&main->scene, &main->ray));
	vec_free(&main->ray.xs.vec);
	aa->sub_pixel++;
}

static void set_blocked_lights(t_main *main)
{
	t_light	light;
	t_ray	ray;
	size_t	i;

	i = 0;
	while (i < main->scene.lights.len)
	{
		light = *(t_light *) vec_get(&main->scene.lights, i);
		ray = ray_new_no_malloc(main->scene.cam.pos, light.direction);
		light.blocked = is_shadowed(&main->scene, &light, &main->scene.cam.pos, &main->ray.hit);
		i++;
	}
	
}

/*
**	anti_aliaing takes multiple samples of the pixel in a checkerboard pattern
**	whitch size is determined by ant_a what you can change in .xml file.
**	By doing this anti_aliasing we can make sharper looking images whit out
**	higher resolution.
*/

int	anti_aliasing(t_main *main, int pixel_x, int pixel_y, int ant_a)
{
	t_anti_aliasing	aa;

	aa.j = 0;
	aa.sub_pixel = 0;
	aa.offset = (1.0 / ant_a);
	aa.color = color_new(0, 0, 0);
	main->ray.hit.color = color_new(0, 0, 0);
	while (aa.j < ant_a)
	{
		aa.i = 0;
		aa.y = ((float)pixel_y + (aa.offset / 2) + (aa.offset * aa.j));
		while (aa.i < ant_a)
		{
			if (ant_a == 1 || (((aa.j % 2 == 0) && (aa.i % 2 == 1))
					|| ((aa.j % 2 == 1) && (aa.i % 2 == 0))))
				aa_help(&aa, main, pixel_x);
			aa.i++;
		}
		aa.j++;
	}
	aa.color = tuple_scalar_div(aa.color, aa.sub_pixel);
	return (color_to_int(aa.color));
}

void	render_image(t_main *main, int task, int ant_al)
{
	t_main	copy;
	int		y;
	int		x;
	int		color;

	y = task;
	copy = (t_main) * main;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			copy.ray.hit.color = color_new(0, 0, 0);
			while (ant_al != 1 && x < WIN_W && main->sdl.frame_buffer.mask[((y
							* WIN_W) + x)] == 0)
				x++;
			if (x == WIN_W)
				break ;
			color = anti_aliasing(&copy, x, y, ant_al);
			main->sdl.frame_buffer.data[((y * WIN_W) + x++)] = color;
		}
		y += NUM_TASKS - 1;
	}
}
