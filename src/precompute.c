/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:04:17 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/18 17:55:31 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	disturb_normal(
	t_tuple *normal,
	t_point hit_point,
	t_perlin *perlin,
	int disturb)
{
	double	perlin_amount;
	t_point	point_perlin;

	if (disturb)
	{
		point_perlin = point_new(hit_point.s_xyzw.x, hit_point.s_xyzw.y,
				hit_point.s_xyzw.z);
		perlin_amount = perlin_noice(point_perlin, perlin);
		perlin_amount *= 0.5;
		normal->s_xyzw.x += perlin_amount * 0.15;
		normal->s_xyzw.y += perlin_amount * 0.15;
		normal->s_xyzw.z += perlin_amount * 0.15;
		*normal = tuple_unit(*normal);
	}
}

static int	store_correct_hit(t_ray *ray, t_scene *scene, t_hit_record *hit,
		t_intersection *closest_t)
{
	hit->neg_hit = FALSE;
	if (closest_t->object->negative == TRUE)
	{
		*closest_t = find_negative_object_intersect(ray, closest_t->i, scene);
		*hit = ray->hit;
		if (hit->hit_dist == INFINITY)
			return (1);
	}
	else
	{
		hit->object = closest_t->object;
		hit->hit_dist = closest_t->t;
		hit->object = closest_t->object;
		hit->hit_loc = ray_position(*ray, hit->hit_dist);
		hit->normal = normal_at(hit->object, hit->hit_loc);
		disturb_normal(&hit->normal, hit->hit_loc, &scene->perlin,
			hit->object->material.normal_disturbance);
		hit->to_eye = tuple_neg(ray->dir);
	}
	return (0);
}

int	precompute(t_ray *ray, t_scene *scene)
{
	t_hit_record	hit;
	t_intersection	closest_t;

	closest_t = find_closest_intersection(&ray->xs);
	if (closest_t.t == INFINITY)
		return (1);
	if (store_correct_hit(ray, scene, &hit, &closest_t) == 1)
		return (1);
	if (vector_dot(hit.normal, hit.to_eye) < 0)
	{
		hit.inside = 1;
		hit.normal = tuple_neg(hit.normal);
	}
	else
		hit.inside = 0;
	hit.over_point = tuple_add(hit.hit_loc,
			tuple_scalar_mult(hit.normal, EPSILON));
	hit.reflect_v = vector_reflect(ray->dir, hit.normal);
	ray->hit = hit;
	ray->hit.surf3_coord = ray_position(ray_transform(ray, \
			&ray->hit.object->inverse_transform), ray->hit.hit_dist);
	ray->hit.surf2_coord = get_surface_coordinate(&ray->hit);
	return (0);
}
