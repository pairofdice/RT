/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:13:33 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/17 15:29:07 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	get_negative_intersects(t_ray *ray, size_t neg_obj_id,
								t_negative *neg_hits)
{
	t_intersection	t;
	size_t			i;
	size_t			hit;

	i = 0;
	hit = 0;
	while (i < ray->xs.vec.len)
	{
		t = *(t_intersection *) vec_get(&ray->xs.vec, i);
		if (t.object->id == neg_obj_id)
		{
			neg_hits->t[hit] = t.t;
			hit = 1;
		}
		i++;
	}
}

int	check_next_obj(t_ray *ray, t_intersection *closest_t, t_scene *scene)
{
	if (closest_t->t != INFINITY && closest_t->object->negative == TRUE)
	{
		*closest_t = find_negative_object_intersect(ray, closest_t->object->id, scene);
		if (closest_t->t == INFINITY)
			return (1);
	}
	else
	{
		ray->hit.hit_dist = closest_t->t;
		if (ray->hit.hit_dist != INFINITY)
		{
			ray->hit.hit_loc = ray_position(*ray, ray->hit.hit_dist);
			ray->hit.object = closest_t->object;
			ray->hit.normal = normal_at(closest_t->object, ray->hit.hit_loc);
			ray->hit.to_eye = tuple_neg(ray->dir);
		}
	}
	return (0);
}

int	find_next_intersection(t_ray *ray, t_intersection *closest_t,
							t_negative *neg_hits, t_scene *scene)
{
	t_intersection	*t;
	size_t			i;

	i = 0;
	closest_t->t = INFINITY;
	while (i < ray->xs.vec.len)
	{
		t = (t_intersection *) vec_get(&ray->xs.vec, i);
		if (t->t > neg_hits->t[1] && t->t < closest_t->t)
			closest_t = t;
		i++;
	}
	return (check_next_obj(ray, closest_t, scene));
}

t_intersection	find_negative_object_intersect(t_ray *ray, int neg_obj_id,
												t_scene *scene)
{
	t_intersection	closest_t;
	t_negative		neg_hits;
	t_object		obj;

	closest_t.t = -1.0;
	get_negative_intersects(ray, neg_obj_id, &neg_hits);
	neg_obj_id = move_negative(ray, neg_obj_id, &neg_hits);
	ray->hit.neg_hit_id = neg_obj_id;
	if (first_positive_object(ray, &closest_t, &neg_hits) == 1)
	{
		ray->hit.neg_hit = 1;
		ray->hit.neg_hit_id = neg_obj_id;
		ray->hit.hit_dist = neg_hits.t[1];
		ray->hit.object = closest_t.object;
		ray->hit.hit_loc = ray_position(*ray, ray->hit.hit_dist);
		obj = *(t_object *) vec_get(&scene->objects, neg_obj_id);
		ray->hit.normal = normal_at(&obj, ray->hit.hit_loc);
		ray->hit.normal = tuple_neg(ray->hit.normal);
		ray->hit.to_eye = tuple_neg(ray->dir);
	}
	else
		find_next_intersection(ray, &closest_t, &neg_hits, scene);
	return (closest_t);
}
