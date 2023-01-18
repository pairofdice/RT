/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:56:08 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 13:48:08 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_tuple	get_spherical(t_tuple obj_space)
{
	t_tuple	map;
	double	math;

	map = point_new(0.0, 0.0, 0.0);
	obj_space = tuple_unit(obj_space);
	math = atan2(obj_space.s_xyzw.z, obj_space.s_xyzw.x);
	math = math / M_PI;
	map.s_xyzw.x = 1 + math * 0.5;
	math = acos(obj_space.s_xyzw.y);
	map.s_xyzw.y = math / M_PI;
	return (map);
}

static t_tuple	get_planar(t_tuple obj_space)
{
	t_tuple	map;

	map = point_new(0.0, 0.0, 0.0);
	map.s_xyzw.x = fmod(obj_space.s_xyzw.x, 1.0);
	map.s_xyzw.y = fmod(obj_space.s_xyzw.z, 1.0);
	return (map);
}

static t_tuple	get_cylindrical(t_tuple obj_space)
{
	t_tuple	polar;

	polar = point_new(0.0, 0.0, 0.0);
	polar.s_xyzw.x = 1 - (atan2(obj_space.s_xyzw.x, obj_space.s_xyzw.z)
			/ (2 * M_PI) + 0.5);
	polar.s_xyzw.y = obj_space.s_xyzw.y - ft_floor(obj_space.s_xyzw.y);
	return (polar);
}

t_tuple	get_surface_coordinate(t_hit_record *hit)
{
	if (hit->object->type == SPHERE)
		return (get_spherical(hit->surf3_coord));
	if (hit->object->type == PLANE)
		return (get_planar(hit->surf3_coord));
	if (hit->object->type == CYLINDER)
		return (get_cylindrical(hit->surf3_coord));
	return (point_new(0.0, 0.0, 0.0));
}
