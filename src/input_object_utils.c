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

int	get_material(t_xml_node *node, t_material *mat)
{
	t_xml_attr	*attr;
	int			index;
	t_tuple		col;

	index = 0;
	while (index < node->attributes.size)
	{
		attr = &node->attributes.list[index];
		if (!ft_strcmp(attr->key, "pattern") && \
		!ft_strcmp(attr->value, "striped"))
			mat->pattern.pattern_id = STRIPED;
		else if (!ft_strcmp(attr->key, "pattern") && \
		!ft_strcmp(attr->value, "grid"))
			mat->pattern.pattern_id = GRID;
		else if (!ft_strcmp(attr->key, "perlin") && \
		!ft_strcmp(attr->value, "true"))
			mat->pattern.pattern_perlin = TRUE;
		index++;
	}
	get_tuple(&col, node->data);
	mat->color = color_new(col.a[0], col.a[1], col.a[2]);
	return (TRUE);
}

int	get_motion(t_xml_node *node, t_motion_blur *motion)
{
	float		speed;
	t_tuple		dir;
	char		*str;

	speed = 0;
	str = xml_node_attr_value(node, "speed");
	if (str)
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

int	get_details(t_xml_node *node, t_object *obj)
{
	if (!ft_strcmp(node->tag, "loc"))
		get_tuple(&obj->loc, node->data);
	else if (!ft_strcmp(node->tag, "up"))
		get_tuple(&obj->up, node->data);
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
