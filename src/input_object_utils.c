/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/13 13:35:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

int	get_motion(t_xml_node *node, t_motion_blur *motion)
{
	float		speed;
	t_tuple		dir;
	char		*str;

	speed = 1.0;
	str = xml_node_attr_value(node, "speed");
	if (str != NULL)
		speed = ft_atof(str);
	get_tuple(&dir, node->data);
	*motion = motion_new(TRUE, speed, tuple_unit(dir));
	return (TRUE);
}

int	get_rotation(t_xml_node *node, t_object *obj)
{
	get_tuple(&obj->rot, node->data);
	obj->rot.a[0] *= M_PI / 180.0;
	obj->rot.a[1] *= M_PI / 180.0;
	obj->rot.a[2] *= M_PI / 180.0;
	return (TRUE);
}

void	get_slice(t_object *obj, char *data, int mode)
{
	int	index;

	index = 0;
	get_tuple(&obj->slice_pos, data);
	obj->slice_pos = tuple_unit(obj->slice_pos);
	obj->slice_toggle = 1;
	while (mode == 1 && index < 4)
	{
		if (obj->slice_pos.a[index] < 0)
			obj->slice_pos.a[index] = 0;
		index++;
	}
	while (mode == 0 && index < 4)
	{
		if (obj->slice_neg.a[index] > 0)
			obj->slice_neg.a[index] = 0;
		index++;
	}
}

int	get_details(t_xml_node *node, t_object *obj)
{
	if (!ft_strcmp(node->tag, "loc"))
		get_tuple(&obj->loc, node->data);
	else if (!ft_strcmp(node->tag, "up"))
		get_tuple(&obj->up, node->data);
	else if (!ft_strcmp(node->tag, "slice_pos"))
	{
		get_tuple(&obj->slice_pos, node->data);
		obj->slice_toggle = 1;
	}
	else if (!ft_strcmp(node->tag, "slice_neg"))
	{
		get_tuple(&obj->slice_neg, node->data);
		obj->slice_toggle = 1;
	}
	else if (!ft_strcmp(node->tag, "rot"))
		get_rotation(node, obj);
	else if (!ft_strcmp(node->tag, "scale"))
		get_tuple(&obj->scale, node->data);
	if (!ft_strcmp(node->tag, "material"))
		get_material(node, &obj->material);
	if (!ft_strcmp(node->tag, "motion"))
		get_motion(node, &obj->motion);
	return (TRUE);
}

int	get_obj_details(t_xml_node *node, t_object *obj)
{
	int			index;

	index = 0;
	while (index < node->children.size)
	{
		if (!get_details(xml_nodelist_at(&node->children, index), obj))
			return (FALSE);
		index++;
	}
	return (TRUE);
}
