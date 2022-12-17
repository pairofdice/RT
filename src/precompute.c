/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:04:17 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/17 17:27:28 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	precompute(t_ray *ray, t_scene *scene)
{
	t_hit_record	hit;
	t_intersection closest_t;

	closest_t = find_closest_intersection(&ray->xs);
	// SEGFAULT FIX
	if (closest_t.t == INFINITY)
		return (1);
	hit.neg_hit = FALSE;
	if (closest_t.object->negative == TRUE)
	{
		closest_t = find_negative_object_intersect(ray, closest_t.i, scene);
		hit = ray->hit;
		if (closest_t.t == INFINITY)
			return (1);
	}
	else
	{
		hit.object = closest_t.object;
		hit.hit_dist = closest_t.t;
		hit.object = closest_t.object;
		hit.hit_loc = ray_position(*ray, hit.hit_dist);
		hit.normal = normal_at(hit.object, hit.hit_loc);
		hit.to_eye = tuple_neg(ray->dir);
	}
	if (vector_dot(hit.normal, hit.to_eye) < 0)
	{
		hit.inside = 1;
		hit.normal = tuple_neg(hit.normal);
	}
	else
		hit.inside = 0;
	hit.over_point = tuple_add(hit.hit_loc, tuple_scalar_mult(hit.normal, EPSILON));
	hit.reflect_v = vector_reflect(ray->dir, hit.normal);
	ray->hit = hit;
	return (0);
}
