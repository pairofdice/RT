/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:09:03 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

t_vec3	get_sphere_normal(t_context *ctx)
{
	t_vec3	result;

	result = vec3_scalar_mult(ctx->ray.dir, ctx->hit.closest_distance);
	result = vec3_add(ctx->ray.orig, result);
	result = vec3_sub(result, ctx->obj.loc);
	result = vec3_unit(result);
	return (result);
}

	// tc = distance along ray closest to sphere center
	// if tc is negative we're looking in the wrong direction
	// d = distance from sphere center to t
	// our ray, so one again pythagoras gives us the closest intersection
	// so, once again
	// d = distance to ray from sphere center
	// if intersection point behind projection plane
	// we now know sphere radius and closest point to sphere center along
	// tc = distance to closest point perpendicular to sphere 
			// center from ray origin
	// tp = distance from d to sphere surface
	// if d is greater than radius of sphere there is no intersection

int	intersects_sphere(t_ray *ray, t_object *sphere, double *distance)
{
	t_vec3	ray_origin_to_sphere;
	double	tc;
	double	d;
	double	tp;
	double	distance_to_intersection;

	ray_origin_to_sphere = vec3_sub(sphere->loc, ray->orig);
	tc = vec3_dot(ray_origin_to_sphere, ray->dir);
	if (tc < 0)
		return (0);
	d = sqrt(fabs(tc * tc - vec3_sqr(ray_origin_to_sphere)));
	if (d > sphere->size)
		return (0);
	tp = sqrt(sphere->size * sphere->size - d * d);
	distance_to_intersection = tc - tp;
	if (distance_to_intersection < 0)
		return (0);
	*distance = distance_to_intersection;
	return (1);
}
