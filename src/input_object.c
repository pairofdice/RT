/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2023/01/19 13:25:48 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/rt.h"

static inline void	populate_types(char (*types)[9])
{
	ft_strcpy(types[0], "sphere");
	ft_strcpy(types[1], "cylinder");
	ft_strcpy(types[2], "plane");
	ft_strcpy(types[3], "cone");
}

int	get_object(t_xml_node *node, t_object *obj)
{
	int			index;
	char		types[4][9];
	char		*value;

	index = 0;
	populate_types(types);
	if (node == NULL || node->attributes.size == 0)
		return (return_error("ERROR: invalid node in get_object"));
	value = xml_node_attr_value(node, "type");
	if (value == NULL)
		return (return_error("ERROR: object has no type"));
	while (index < 4)
	{
		if (!ft_strcmp(value, types[index]))
			*obj = object_new(index);
		index++;
	}
	obj->negative = FALSE;
	value = xml_node_attr_value(node, "negative");
	if (value != NULL && !ft_strcmp(value, "true"))
		obj->negative = TRUE;
	if (!get_obj_details(node, obj))
		return (return_error("ERROR: get_obj_details failed"));
	return (TRUE);
}
