/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glare.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:41:59 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/22 15:07:36 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	set_blocked_lights(t_main *main)
{
	t_light	*light;
	t_ray	ray;
	size_t	i;

	i = 0;
	while (i < main->scene.lights.len)
	{
		light = (t_light *)vec_get(&main->scene.lights, i);
		ray = ray_new(main->scene.cam.pos,
				tuple_unit(tuple_sub(main->scene.cam.pos, light->location)));
		scene_intersect(&main->scene, &ray);
		light->blocked = is_shadowed(&main->scene, light, &main->scene.cam.pos,
				&ray.hit);
		vec_free(&ray.xs.vec);
		i++;
	}
}

t_color	glare(t_ray *ray, t_vec *lights)
{
	t_color	result_glare;
	t_color	glare;
	t_light	light;
	size_t	i;
	double	dot;

	result_glare = color_new(0, 0, 0);
	i = 0;
	while (i < lights->len)
	{
		glare = color_new(0, 0, 0);
		light = *(t_light *)vec_get(lights, i);
		dot = vector_dot(tuple_unit(tuple_neg(tuple_sub(ray->orig,
							light.location))), tuple_unit(ray->dir));
		if (dot > 0.995 && light.blocked == 0)
		{
			dot = pow(dot, 2024);
			glare = tuple_add(glare, tuple_scalar_mult(light.intensity, dot));
			glare = tuple_scalar_mult(glare, 4);
			result_glare = tuple_add(glare, result_glare);
		}
		i++;
	}
	return (result_glare);
}
