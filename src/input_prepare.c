/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_prepare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/13 13:35:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

int	return_error(const char *str)
{
	ft_putendl_fd(str, 2);
	return (FALSE);
}

int	prepare_objects(t_xml_nodelist *list, t_vec *objects)
{
	t_matrix	rotate;
	t_object	obj;
	int			index;

	index = 0;
	if (list->size == 0)
		return (return_error("ERROR: no objects in input"));
	while (index < list->size)
	{
		if (!get_object(xml_nodelist_at(list, index), &obj))
			return (FALSE);
		obj.transform = matrix_translate_2(obj.loc);
		rotate = matrix_rotate_x(obj.rot.a[0]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		rotate = matrix_rotate_y(obj.rot.a[1]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		rotate = matrix_rotate_z(obj.rot.a[2]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		rotate = matrix_scale(obj.scale.a[0], obj.scale.a[1], obj.scale.a[2]);
		obj.transform = matrix_multiply(&obj.transform, &rotate);
		obj.inverse_transform = matrix_inverse(&obj.transform);
		obj.id = index++;
		vec_push(objects, &obj);
	}
	return (TRUE);
}

void	initialize_camera_2(t_cam *cam, t_matrix transform)
{
	cam->c = tuple_sub(point_new(0, 0, 0), tuple_scalar_mult(cam->n, 0.1));
	cam->plane_h = tan(1.04719 / 2) * 2 * 0.1;
	cam->plane_w = cam->plane_h * ((float)WIN_W / WIN_H);
	cam->l = tuple_sub(cam->c,
			tuple_scalar_mult(cam->u, (cam->plane_w / 2.0)));
	cam->l = tuple_sub(cam->l,
			tuple_scalar_mult(cam->v, cam->plane_h / 2.0));
	cam->transform = coi_transform(cam, transform);
}

int	prepare_camera(t_xml_nodelist *list, t_cam *cam)
{
	t_matrix	scale;

	if (list->size != 1)
	{
		if (list->size < 1)
			return (return_error("ERROR: no camera in input"));
		if (list->size > 1)
			return (return_error("ERROR: too many cameras in input"));
	}
	cam->coi = point_new(0.0, 0.0, 0.0);
	scale = matrix_scale(1, 1, 1);
	get_camera(list->list[0], cam);
	cam->transform = matrix_translate_2(cam->pos);
	cam->coi_transform = matrix_translate_2(cam->coi);
	cam->transform = matrix_multiply(&cam->transform, &scale);
	cam->motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1, 0, 0)));
	cam->coi_motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1, 0, 0)));
	initialize_camera(cam, cam->transform);
	return (TRUE);
}

int	prepare_lights(t_xml_nodelist *list, t_vec *lights)
{
	int			index;
	t_light		light;
	t_xml_node	*node;
	char		*value;

	index = 0;
	if (list->size == 0)
		return (return_error("ERROR: no lights in input"));
	while (index < list->size)
	{
		node = xml_nodelist_at(list, index);
		value = xml_node_attr_value(node, "type");
		if (!ft_strcmp(value, "sun"))
			light.type = SUN;
		else
			light.type = POINT;
		get_light(node, &light);
		vec_push(lights, &light);
		index++;
	}
	return (TRUE);
}
