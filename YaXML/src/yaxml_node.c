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

t_xml_node	*xml_node_new(t_xml_node *parent)
{
	t_xml_node	*new;

	new = (t_xml_node *)malloc(sizeof(t_xml_node));
	if (new == NULL)
		return (NULL);
	new->parent = parent;
	new->tag = NULL;
	new->data = NULL;
	if (!xml_attrlist_init(&new->attributes) || \
	!xml_nodelist_init(&new->children))
		return (NULL);
	if (parent)
	{
		if (!xml_nodelist_add(&parent->children, new))
			return (NULL);
	}
	return (new);
}

t_xml_node	*xml_node_child(t_xml_node *parent, int index)
{
	return (parent->children.list[index]);
}

t_xml_nodelist	*xml_node_children(t_xml_node *parent, const char *tag)
{
	t_xml_nodelist	*list;
	t_xml_node		*child;
	int				index;

	index = 0;
	list = (t_xml_nodelist *)malloc(sizeof(t_xml_nodelist));
	if (list == NULL)
		return (NULL);
	if (!xml_nodelist_init(list))
		return (NULL);
	while (index < parent->children.size)
	{
		child = parent->children.list[index];
		if (!ft_strcmp(child->tag, tag))
		{
			if (!xml_nodelist_add(list, child))
				return (NULL);
		}
		index++;
	}
	return (list);
}

t_xml_node	*xml_node_tag(t_xml_nodelist *list, char *tag)
{
	t_xml_node	*node;
	int			index;

	index = 0;
	while (index < list->size)
	{
		node = list->list[index];
		if (!ft_strcmp(node->tag, tag))
			return (node);
		index++;
	}
	return (NULL);
}
