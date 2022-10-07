/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:50:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:13:25 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	test_sphere(t_ray normal,
				t_vec3 to_light,
				t_object *obj,
				double *distance)
{
	if (intersects_sphere(&(t_ray){normal.orig, vec3_unit(to_light)},
		obj,
		distance))
	{
		if (*distance + LIGHTBULB_SIZE < vec3_mag(to_light))
			return (0);
	}
	return (1);
}

int	test_plane(t_ray normal,
				t_vec3 to_light,
				t_object *obj,
				double *distance)
{
	if (intersects_plane(&(t_ray){normal.orig, vec3_unit(to_light)},
		obj,
		distance))
	{
		if (*distance + LIGHTBULB_SIZE < vec3_mag(to_light))
			return (0);
	}
	return (1);
}

int	test_cone(t_ray normal,
				t_vec3 to_light,
				t_object *obj,
				double *distance)
{
	if (intersects_cone(&(t_ray){normal.orig, vec3_unit(to_light)},
		obj,
		distance))
	{
		if (*distance + LIGHTBULB_SIZE < vec3_mag(to_light))
			return (0);
	}
	return (1);
}

int	test_cylinder(t_ray normal,
				t_vec3 to_light,
				t_object *obj,
				double *distance)
{
	if (intersects_cylinder(&(t_ray){normal.orig, vec3_unit(to_light)},
		obj,
		distance))
	{
		if (*distance + LIGHTBULB_SIZE < vec3_mag(to_light))
			return (0);
	}
	return (1);
}
