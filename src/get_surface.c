/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_surface.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:56:08 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/27 11:14:21 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_tuple	get_spherical(t_tuple obj_space)
{
	t_tuple	map;

	obj_space = tuple_unit(obj_space);
	map.s_xyzw.x = (atan2(obj_space.s_xyzw.x, obj_space.s_xyzw.z) \
	/ TWOPI + 0.5);
	map.s_xyzw.y = (acos(obj_space.s_xyzw.y) * M_1_PI);
	return (map);
}

static t_tuple	get_planar(t_tuple obj_space)
{
	t_tuple	map;

	map = point_new((fmod(obj_space.s_xyzw.x, 1.0)),
			((fmod(obj_space.s_xyzw.z, 1.0))), 0.0);
	if (map.s_xyzw.x < 0)
		map.s_xyzw.x += 1.0;
	if (map.s_xyzw.y < 0)
		map.s_xyzw.y += 1.0;
	return (map);
}

static t_tuple	get_cylinderic(t_tuple obj_space)
{
	t_tuple	map;

	map = vector_new(0, 0, 0);
	map.s_xyzw.x = 1 - atan2(obj_space.s_xyzw.x, obj_space.s_xyzw.z) \
	/ TWOPI + 0.5;
	map.s_xyzw.y = obj_space.s_xyzw.y * 0.5 - ft_floor(obj_space.s_xyzw.y);
	if (map.s_xyzw.x < 0)
		map.s_xyzw.x += 1.0;
	if (map.s_xyzw.y < 0)
		map.s_xyzw.y += 1.0;
	return (map);
}

t_tuple	get_surface_coordinate(t_hit_record *hit)
{
	if (hit->object->type == SPHERE)
		return (get_spherical(hit->surf3_coord));
	if (hit->object->type == PLANE)
		return (get_planar(hit->surf3_coord));
	if (hit->object->type == CYLINDER || hit->object->type == CONE)
		return (get_cylinderic(hit->surf3_coord));
	return (point_new(0.0, 0.0, 0.0));
}
