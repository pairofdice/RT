/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflected_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:18:54 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/11 13:12:06 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	reflected_color(t_scene *scene, t_ray *ray)
{
	t_color	color;
	double	reflectiv;

	reflectiv = ray->hit.object->material.reflective;
	color = color_new(0, 0, 0);
	if (ray->remaining <= 0 || ray->hit.object->material.reflective < EPSILON)
		return (color);
	ray->remaining--;
	ray->orig = ray->hit.over_point;
	ray->dir = ray->hit.reflect_v;
	vec_free(&ray->xs.vec);
	vec_new(&ray->xs.vec, 2, sizeof(t_intersection));
	color = color_at(scene, ray);
	color = tuple_scalar_mult(color, reflectiv);
	return (color);
}
