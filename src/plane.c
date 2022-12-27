/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:23:05 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/12 14:16:52 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	intersect_plane(t_ray *inc_ray, t_object *s)
{
	double			t;
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	ray = ray_transform(inc_ray, &s->inverse_transform);
	if (fabs(ray.dir.s_xyzw.y) < EPSILON)
		return (0);
	t = ((-ray.orig.s_xyzw.y) / ray.dir.s_xyzw.y);
	if (t < 0)
		return (0);
	intersection_record(inc_ray, t, s);
	return (1);
}
