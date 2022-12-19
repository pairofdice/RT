/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:17:15 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/29 10:17:17 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaxml.h"

void	xml_attr_free(t_xml_attr *attr)
{
	if (attr->key)
		free(attr->key);
	if (attr->value)
		free(attr->value);
}

void	xml_attrlist_free(t_xml_attrlist *attributes)
{
	int	index;

	index = 0;
	while (index < attributes->size)
	{
		xml_attr_free(&attributes->list[index]);
		index++;
	}
	free(attributes->list);
}

void	xml_nodelist_free(t_xml_nodelist *children)
{
	int	index;

	index = 0;
	while (index < children->size)
	{
		xml_node_free(children->list[index]);
		index++;
	}
	free(children->list);
}

void	xml_node_free(t_xml_node *node)
{
	if (node->tag)
		free(node->tag);
	if (node->data)
		free(node->data);
	xml_attrlist_free(&node->attributes);
	xml_nodelist_free(&node->children);
	free(node);
}

void	xml_doc_free(t_xml_doc *doc)
{
	if (doc->version)
		free(doc->version);
	if (doc->encoding)
		free(doc->encoding);
	if (doc->head)
		xml_node_free(doc->head);
}
