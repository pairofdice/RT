/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:23:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 17:49:44 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_color	shade(t_object obj, double shading)
{
	t_color	c;

	shading += AMBIENT;
	c.x = obj.color.x * shading * 100 * 255;
	c.x += shading * 1000.0;
	c.x = pow(c.x, 1 / GAMMA) * 15;
	if (c.x >= 255)
		c.x = 255;
	c.y = obj.color.y * shading * 100 * 255;
	c.y += shading * 1000.0;
	c.y = pow(c.y, 1 / GAMMA) * 15;
	if (c.y >= 255)
		c.y = 255;
	c.z = obj.color.z * shading * 100 * 255;
	c.z += shading * 1000.0;
	c.z = pow(c.z, 1 / GAMMA) * 15;
	if (c.z >= 255)
		c.z = 255;
	return (c);
}

static double	sf_calc_normal_light_dot(t_ray ray,
										t_ray normal,
										t_vec3 to_light)
{
	double	dot;

	dot = vec3_dot(normal.dir, vec3_unit(to_light));
	vec3_dot(vec3_neg(ray.dir), normal.dir);
	if (dot < 0)
		dot = 0;
	dot = dot / (vec3_mag(to_light) * vec3_mag(to_light));
	return (dot);
}

int	test_objects(t_context *ctx, t_object obj, t_ray normal, t_vec3 to_light)
{
	if (obj.type == SPHERE)
	{
		if (!test_sphere(normal, to_light, &obj, &ctx->hit.closest_distance))
			return (0);
	}
	if (obj.type == PLANE)
	{
		if (!test_plane(normal, to_light, &obj, &ctx->hit.closest_distance))
			return (0);
	}
	if (obj.type == CYLINDER)
	{
		if (!test_cylinder(normal, to_light, &obj, &ctx->hit.closest_distance))
			return (0);
	}
	if (obj.type == CONE)
	{
		if (!test_cone(normal, to_light, &obj, &ctx->hit.closest_distance))
			return (0);
	}
	return (1);
}

// Shoot a ray from the hit location a/the light and check if any intersecting
// surface is closer than the light
static int	sf_shadow_object_intersect(t_context *ctx,
							t_ray normal,
							t_vec3 to_light,
							int id)
{
	t_object	obj;
	size_t		i;

	i = 0;
	while (i < ctx->scene.len)
	{
		if ((int)i == id)
		{
			i++;
			continue ;
		}
		obj = *(t_object *)vec_get(&ctx->scene, i);
		if (!test_objects(ctx, obj, normal, to_light))
			return (0);
		i++;
	}
	return (1);
}

double	get_light_level(t_ray normal, t_ray ray, t_context *ctx, int id)
{
	t_vec3	to_light;

	to_light = vec3_sub(ctx->light.loc, normal.orig);
	ctx->hit.closest_distance = vec3_mag(to_light);
	ctx->hit.closest_distance -= LIGHTBULB_SIZE;
	if (!sf_shadow_object_intersect(ctx, normal, to_light, id))
		return (0.0);
	return (sf_calc_normal_light_dot(ray, normal, to_light));
}
