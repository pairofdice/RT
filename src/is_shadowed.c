/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:43:31 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/12 19:34:43 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/object.h"
#include "../include/rt.h"

static void	set_light_params(
	t_light_params *params,
	t_light *light,
	t_point *point)
{
	if (light->type == POINT)
	{
		params->to_light = tuple_sub(light->location, *point);
		params->distance = tuple_mag(params->to_light);
		params->direction = tuple_unit(params->to_light);
	}
	else
	{
		params->to_light = tuple_sub(light->location, point_new(0.0, 0.0, 0.0));
		params->to_light = tuple_unit(params->to_light);
		params->distance = MAX_DISTANCE;
		params->direction = tuple_unit(params->to_light);
	}
}

int	is_shadowed(
	t_scene *scene,
	t_light *light,
	t_point *point,
	t_hit_record *hit)
{
	t_light_params	lt_prms;
	t_intersection	intersection;
	t_ray			ray;

	set_light_params(&lt_prms, light, point);
	ray = ray_new(*point, lt_prms.direction);
	scene_intersect(scene, &ray);
	if (ray.xs.vec.len > 0)
	{
		if (hit->neg_hit == FALSE)
			intersects_from_positive_surface(scene, &intersection, &ray);
		else
			intersection = find_shadow_true_negatives(ray, lt_prms.distance,
					scene);
		if ((intersection.t < lt_prms.distance && intersection.t > 0))
		{
			vec_free(&ray.xs.vec);
			return (1);
		}
	}
	vec_free(&ray.xs.vec);
	return (0);
}
