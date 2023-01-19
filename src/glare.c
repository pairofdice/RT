/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glare.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:41:59 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 15:01:49 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	set_blocked_lights(t_main *main)
{
	t_light	light;
	t_ray	ray;
	size_t	i;

	i = 0;
	while (i < main->scene.lights.len)
	{
		light = *(t_light *)vec_get(&main->scene.lights, i);
		ray = ray_new_no_malloc(main->scene.cam.pos,
				tuple_sub(main->scene.cam.pos, light.location));
		light.blocked = is_shadowed(&main->scene, &light, &main->scene.cam.pos,
				&main->ray.hit);
		i++;
	}
}

t_color	glare(t_ray *ray, t_vec *lights)
{
	t_color	glare;
	t_light	light;
	size_t	i;
	double	dot;
	double	dotdotdot;

	glare = color_new(0, 0, 0);
	i = 0;
	while (i < lights->len)
	{
		light = *(t_light *)vec_get(lights, i);
		dot = vector_dot(tuple_unit(tuple_neg(tuple_sub(ray->orig,
							light.location))), tuple_unit(ray->dir));
		if (dot > 0.999)
		{
			dotdotdot = pow(dot, 2024);
			glare = tuple_add(glare, color_new(light.intensity.s_rgb.r
						* dotdotdot, light.intensity.s_rgb.g * dotdotdot,
						light.intensity.s_rgb.b * dotdotdot));
		}
		i++;
	}
	return (glare);
}
