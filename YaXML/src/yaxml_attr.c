/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:35:23 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/29 10:35:25 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaxml.h"

char	*xml_node_attr_value(t_xml_node *node, char *key)
{
	t_xml_attr	attr;
	int			index;

	index = 0;
	while (index < node->attributes.size)
	{
		attr = node->attributes.list[index];
		if (attr.key != 0 && !ft_strcmp(attr.key, key))
			return (attr.value);
		index++;
	}
	return (NULL);
}

t_xml_attr	*xml_node_attr(t_xml_node *node, char *key)
{
	t_xml_attr	*attr;
	int			index;

	index = 0;
	while (index < node->attributes.size)
	{
		attr = &node->attributes.list[index];
		if (!ft_strcmp(attr->key, key))
			return (attr);
		index++;
	}
	return (NULL);
}
