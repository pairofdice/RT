/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:22:13 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/11 13:15:09 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color	shade_hit(t_scene *scene, t_ray *ray)
{
	t_color		result;
	t_color		temp_color;
	t_light		light;
	size_t		i;
	t_ray		temp;

	i = 0;
	result = color_new(0, 0, 0);
	while (i < scene->lights.len)
	{
		light = *(t_light *)vec_get(&scene->lights, i++);
		ray->hit.is_shadowed = is_shadowed(scene, &light, &ray->hit.over_point,
				&ray->hit);
		temp_color = lighting(&light, &ray->hit);
		if (ray->hit.object->material.pattern.pattern_id != NONE)
		{
			temp.orig = ray_position(ray_transform(ray, \
			&ray->hit.object->inverse_transform), ray->hit.hit_dist);
			temp_color = pattern_at(ray->hit, temp.orig, temp_color,
					scene->perlin);
		}
		result = tuple_add(result, temp_color);
		result = tuple_add(result, reflected_color(scene, ray));
	}
	return (result);
}
