/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:49:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/17 17:19:03 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "../include/object.h"


// int	intersection_compare(const void *i_a, const void *i_b)
// {
// 	t_intersection left = *(const t_intersection *) i_a;
// 	t_intersection right = *(const t_intersection *) i_b;

// 	if (nearly_equal(left.t, right.t))
// 		return (0);
// 	return ((left.t > right.t) - (left.t < right.t));
// }

t_color	color_at(t_scene *scene, t_ray *ray)
{
	t_color	color;

	scene_intersect(scene, ray);
	if (ray->xs.vec.len == 0)
		return (color_new(0, 0, 0));
	if (precompute(ray, scene) == 1 || ray->hit.hit_dist > MAX_DISTANCE)
		return (color_new(0, 0, 0));
	color = shade_hit(scene, ray);
	return (color);
}

// t_color	shade_hit(t_scene *scene, t_ray *ray)
// {
// 	t_color	result;
// 	t_color	temp_color;
// 	t_color	reflected;
// 	t_light	light;
// 	size_t	i;
	

// 	i = 0;
// 	result = color_new(0, 0, 0);
// 	while (i < scene->lights.len)
// 	{
// 		light = *(t_light *)vec_get(&scene->lights, i);
// 		temp_color = lighting(&ray->hit.object->material, 
// 								light, ray->hit.hit_loc, 
// 								ray->hit.to_eye, 
// 								ray->hit.normal, 
// 								is_shadowed(scene, light,  ray->hit.over_point));
// 		result = tuple_add(result, temp_color);
// /* 		if (ray->hit.object->material.reflective > EPSILON)
// 		{ */
// 			reflected = reflected_color(scene, ray);
// 			result = tuple_add(result, reflected);
// /* 		} */
// 		i++;
// 	}
// 	return (result);
// }
