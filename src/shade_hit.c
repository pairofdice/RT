/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:22:13 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 13:11:44 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color	texture_int_to_color(unsigned int rgba)
{
	t_color	color;

	color.s_rgb.b = (rgba) % 256;
	color.s_rgb.g = (rgba >> 8) % 256;
	color.s_rgb.r = (rgba >> 16) % 256;
	color.s_xyzw.w = 0;
	return (color);
}

static t_color	get_texture(t_hit_record *hit)
{
	t_color	color;
	int		i_color;
	int		t_x;
	int		t_y;

	if (hit->object->texture.loaded == FALSE)
		return (hit->object->material.color);
	t_x = ((int)(hit->object->texture.w * hit->surf2_coord.s_xyzw.x));
	t_y = ((int)(hit->object->texture.h * hit->surf2_coord.s_xyzw.y));
	i_color = hit->object->texture.pixels[(t_y * hit->object->texture.w) + t_x];
	color = texture_int_to_color(i_color);
	color = tuple_scalar_div(color, 255);
	return (color);
}

t_color	shade_hit(t_scene *scene, t_ray *ray)
{
	t_color		result;
	t_color		phong;
	t_color		color;
	t_light		light;
	size_t		i;

	i = 0;
	result = color_new(0, 0, 0);
	phong = color_new(0, 0, 0);
	color = get_texture(&ray->hit);
	if (ray->hit.object->material.pattern.pattern_id != NONE)
		color = pattern_at(ray->hit, ray->hit.hit_loc, \
		color, scene->perlin);
	while (i < scene->lights.len)
	{
		light = *(t_light *)vec_get(&scene->lights, i++);
		ray->hit.is_shadowed = is_shadowed(scene, &light, &ray->hit.over_point, \
				&ray->hit);
		result = tuple_add(result, lighting(&light, &ray->hit, &phong, color));
	}
	result = tuple_add(result, tuple_scalar_mult(color, ray->hit.object->material.ambient));
	if (ray->hit.object->material.reflective > 0)
		result = tuple_add(tuple_scalar_mult(result, 1 - \
		ray->hit.object->material.reflective), reflected_color(scene, ray));
	return (tuple_add(result, phong));
}
