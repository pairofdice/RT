/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:12:38 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/12 19:36:34 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <math.h>

static void	lighting_get_diffuse_and_specular(
	t_lighting *lighting,
	t_material *mat,
	t_hit_record *hit,
	t_light *light)
{
	if (lighting->light_dot_normal < 0 || hit->is_shadowed == 1)
	{
		lighting->diffuse = color_new(0, 0, 0);
		lighting->specular = color_new(0, 0, 0);
	}
	else
	{
		lighting->diffuse = tuple_scalar_mult(lighting->effective_color,
				mat->diffuse * lighting->light_dot_normal);
		lighting->reflection_v = vector_reflect(tuple_neg(lighting->to_light_v),
				hit->normal);
		lighting->reflection_dot_eye = vector_dot(lighting->reflection_v,
				hit->to_eye);
		if (lighting->reflection_dot_eye <= 0)
			lighting->specular = color_new(0, 0, 0);
		else
		{
			lighting->factor = pow(lighting->reflection_dot_eye,
					mat->shininess);
			lighting->specular = tuple_scalar_mult(light->intensity,
					mat->specular * lighting->factor);
		}
	}
}

static t_vector	to_light(t_light *light, t_hit_record *hit)
{
	t_vector	result;

	if (light->type == POINT)
	{
		result = tuple_unit(tuple_sub(light->location, hit->hit_loc));
	}
	else
		result = tuple_unit(tuple_sub(light->location, point_new(0.0, 0.0,
						0.0)));
	return (result);
}

t_color	lighting(t_light *light, t_hit_record *hit, t_color *phong)
{
	t_lighting	lighting;
	t_material	mat;

	mat = hit->object->material;
	lighting.result = color_new(0, 0, 0);
	lighting.result.s_xyzw.w = 1;
	lighting.effective_color = color_multiply(hit->object->material.color,
			light->intensity);
	lighting.to_light_v = to_light(light, hit);
	lighting.ambient = tuple_scalar_mult(lighting.effective_color, mat.ambient);
	lighting.light_dot_normal = vector_dot(lighting.to_light_v, hit->normal);
	lighting_get_diffuse_and_specular(&lighting, &mat, hit, light);
	*phong = tuple_add(*phong, tuple_add(lighting.diffuse, lighting.specular));
	lighting.result = tuple_add(lighting.result, lighting.ambient);
	lighting.result.s_xyzw.w = 0;
	return (lighting.result);
}
