/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:41:16 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:48:06 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	intersect_sphere(t_ray *inc_ray, t_object *obj)
{
	t_abcd			abcd;
	double			t[2];
	t_ray			ray;

	ray = ray_new_no_malloc(inc_ray->orig, inc_ray->dir);
	ray = ray_transform(inc_ray, &obj->inverse_transform);
	ray.orig.s_xyzw.w = 0.0;
	abcd.a = vector_dot(ray.dir, ray.dir);
	abcd.b = 2 * vector_dot(ray.dir, ray.orig);
	abcd.c = vector_dot(ray.orig, ray.orig) - 1;
	abcd.d = calc_discriminant(abcd.a, abcd.b, abcd.c);
	if (abcd.d < 0)
		return (0);
	t[0] = (-(abcd.b) - sqrt(abcd.d)) / (2 * abcd.a);
	t[1] = (-(abcd.b) + sqrt(abcd.d)) / (2 * abcd.a);
	return (slice(inc_ray, t, obj, &ray));
}
