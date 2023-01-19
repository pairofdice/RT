/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:43:31 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:34:37 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_intersection	get_first_intersect(t_ray *ray, t_negative *n)
{
	t_intersection	t;

	t.t = INFINITY;
	n->i = 0;
	while (n->i < ray->xs.vec.len)
	{
		n->t2 = *(t_intersection *)vec_get(&ray->xs.vec, n->i);
		if (n->t2.t > n->t[1] && n->t2.t < t.t)
			t = n->t2;
		n->i++;
	}
	return (t);
}

static size_t	get_first_neg_intersect(t_ray *ray, double dist, t_negative *n)
{
	size_t	neg_id;

	n->i = 0;
	while (n->i < ray->xs.vec.len)
	{
		n->t1 = *(t_intersection *)vec_get(&ray->xs.vec, n->i);
		if (n->t1.object->negative == TRUE)
		{
			if (n->t1.t < dist && n->t1.t < n->t[0])
			{
				n->t[0] = n->t1.t;
				neg_id = n->t1.object->id;
			}
		}
		n->i++;
	}
	return (neg_id);
}

t_intersection	find_shadow_true_negatives(
	t_ray ray,
	double dist,
	t_scene *scene)
{
	t_intersection	t;
	t_negative		n;
	size_t			neg_id;

	n.t[0] = INFINITY;
	n.t[1] = INFINITY;
	neg_id = get_first_neg_intersect(&ray, dist, &n);
	get_negative_intersects(&ray, neg_id, &n);
	move_negative(&ray, neg_id, &n);
	t = get_first_intersect(&ray, &n);
	if (t.t != INFINITY && t.object->negative == TRUE)
		t = find_negative_object_intersect(&ray, t.t, scene);
	return (t);
}

void	intersects_from_positive_surface(
	t_scene *scene,
	t_intersection *intersection,
	t_ray *ray)
{
	*intersection = find_closest_intersection(&ray->xs);
	if (intersection->t != INFINITY && intersection->object->negative == TRUE)
	{
		*intersection = find_negative_object_intersect(
				ray,
				intersection->i,
				scene);
		intersection->t = ray->hit.hit_dist;
	}
}
