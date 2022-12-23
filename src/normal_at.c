/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:08:01 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/15 12:50:53 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static void	cone_normal(t_point *obj_point, t_vector *obj_normal)
{
	obj_normal->s_xyzw.x = obj_point->s_xyzw.x;
	obj_normal->s_xyzw.z = obj_point->s_xyzw.z;
	obj_normal->s_xyzw.w = 0;
	obj_normal->s_xyzw.y = sqrt(obj_point->s_xyzw.x * obj_point->s_xyzw.x
			+ obj_point->s_xyzw.z * obj_point->s_xyzw.z);
	if (obj_point->s_xyzw.y > 0)
		obj_normal->s_xyzw.y = -obj_normal->s_xyzw.y;
}

t_vector	normal_at(t_object *obj, t_point point)
{
	t_point		obj_point;
	t_vector	obj_normal;
	t_vector	world_normal;
//	t_matrix	obj->inverse_transform;
	t_matrix	temp;

//	obj->inverse_transform = matrix_obj->inverse_transform(&obj->transform);
	temp = obj->inverse_transform;
	obj_point = matrix_tuple_multiply(&obj->inverse_transform, &point);
	if (obj->type == SPHERE)
		obj_normal = tuple_sub(obj_point, point_new(0, 0, 0));
	if (obj->type == CYLINDER)
	{
		obj_normal = obj_point;
		obj_normal.s_xyzw.y = 0;
	}
	if (obj->type == PLANE)
		obj_normal = vector_new(0, 1, 0);
	if (obj->type == CONE)
		cone_normal(&obj_point, &obj_normal);
	matrix_transpose(&temp);
	world_normal = matrix_tuple_multiply(&temp, &obj_normal);
	world_normal.s_xyzw.w = 0;
	return (tuple_unit(world_normal));
}
