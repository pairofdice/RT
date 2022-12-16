/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflected_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:18:54 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/16 15:52:29 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	reflected_color(t_scene *scene, t_ray *ray)
{
	t_color	color;

	color = color_new(0, 0, 0);
	if (ray->remaining <= 0 || ray->hit.object->material.reflective < EPSILON)
		return (color);
	ray->remaining--;
	ray->orig = ray->hit.over_point;
	ray->dir = ray->hit.reflect_v;
	vec_free(&ray->xs.vec);
	vec_new(&ray->xs.vec, 2, sizeof(t_intersection));
	color = color_at(scene, ray);
	color = tuple_scalar_mult(color, ray->hit.object->material.reflective);
	return (color);
}
