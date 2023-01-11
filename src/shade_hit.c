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
	t_color		phong;
	t_light		light;
	size_t		i;

	i = 0;
	result = color_new(0, 0, 0);
	phong = color_new(0, 0, 0);
	while (i < scene->lights.len)
	{
		light = *(t_light *)vec_get(&scene->lights, i++);
		ray->hit.is_shadowed = is_shadowed(scene, &light, &ray->hit.over_point, \
				&ray->hit);
		temp_color = lighting(&light, &ray->hit, &phong);
		if (ray->hit.object->material.pattern.pattern_id != NONE)
			temp_color = pattern_at(ray->hit, ray_position(ray_transform(ray, \
			&ray->hit.object->inverse_transform), ray->hit.hit_dist), \
			temp_color, scene->perlin);
		result = tuple_add(result, temp_color);
	}
	if (ray->hit.object->material.reflective > 0)
		result = tuple_add(tuple_scalar_mult(result, 1 - \
		ray->hit.object->material.reflective), reflected_color(scene, ray));
	return (tuple_add(result, phong));
}
