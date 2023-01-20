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

void	get_surface(t_xml_node *surface, t_material *mat)
{
	char		*attr_value;

	attr_value = xml_node_attr_value(surface, "ambient");
	if (attr_value)
		mat->ambient = ft_atof(attr_value);
	attr_value = xml_node_attr_value(surface, "diffuse");
	if (attr_value)
		mat->diffuse = ft_atof(attr_value);
	attr_value = xml_node_attr_value(surface, "specular");
	if (attr_value)
		mat->specular = ft_atof(attr_value);
	attr_value = xml_node_attr_value(surface, "shininess");
	if (attr_value)
		mat->shininess = ft_atof(attr_value);
	attr_value = xml_node_attr_value(surface, "reflective");
	if (attr_value)
		mat->reflective = ft_atof(attr_value);
	attr_value = xml_node_attr_value(surface, "normal_disturbance");
	if (attr_value)
		mat->normal_disturbance = ft_atoi(attr_value);
	attr_value = xml_node_attr_value(surface, "pattern_dif");
	if (attr_value)
		mat->pattern.pattern_dif = ft_atof(attr_value);
}

int	get_material_details(t_xml_node *node, t_material *mat, t_object *obj)
{
	int			index;
	t_tuple		col;
	t_xml_node	*temp;

	index = 0;
	while (index < node->children.size)
	{
		temp = xml_node_child(node, index);
		if (!ft_strcmp(temp->tag, "color"))
		{
			get_tuple(&col, temp->data);
			mat->color = color_new(col.a[0], col.a[1], col.a[2]);
		}
		else if (!ft_strcmp(temp->tag, "surface"))
			get_surface(temp, mat);
		else if (!ft_strcmp(temp->tag, "texture"))
			image_load(temp->data, &obj->texture);
		index++;
	}
	return (TRUE);
}

int	get_material(t_xml_node *node, t_material *mat, t_object *obj)
{
	t_xml_attr	*attr;
	int			index;

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
	get_material_details(node, mat, obj);
	return (TRUE);
}
