/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:59:39 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/29 10:59:40 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaxml.h"

void	*resize_memory(void *ptr, size_t size, size_t old_size)
{
	void	*new;

	new = malloc(size);
	if (new == NULL || (size <= 0 && ptr != NULL))
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (ptr == 0)
		return (new);
	if (size < old_size)
		old_size = size;
	ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}

int	xml_attrlist_init(t_xml_attrlist *list)
{
	list->memory_size = 1;
	list->size = 0;
	list->list = (t_xml_attr *)malloc(sizeof(t_xml_attr) * list->memory_size);
	if (list->list == NULL)
		return (FALSE);
	return (TRUE);
}

int	xml_attrlist_add(t_xml_attrlist *list, t_xml_attr *attr)
{
	if (list->size >= list->memory_size)
	{
		list->memory_size *= 2;
		list->list = (t_xml_attr *)resize_memory(list->list, \
		sizeof(t_xml_attr) * list->memory_size, \
		sizeof(t_xml_attr) * list->size);
		if (list->list == NULL)
			return (FALSE);
	}
	list->list[list->size++] = *attr;
	return (TRUE);
}

int	xml_nodelist_init(t_xml_nodelist *list)
{
	list->memory_size = 1;
	list->size = 0;
	list->list = (t_xml_node **)malloc(sizeof(t_xml_node *) * \
	list->memory_size);
	if (list->list == NULL)
		return (FALSE);
	return (TRUE);
}

int	xml_nodelist_add(t_xml_nodelist *list, t_xml_node *node)
{
	if (list->size >= list->memory_size)
	{
		list->memory_size *= 2;
		list->list = (t_xml_node **)resize_memory(list->list, \
		sizeof(t_xml_node *) * list->memory_size, \
		sizeof(t_xml_node *) * list->size);
		if (list->list == NULL)
			return (FALSE);
	}
	list->list[list->size++] = node;
	return (TRUE);
}

t_xml_node	*xml_nodelist_at(t_xml_nodelist *list, int index)
{
	return (list->list[index]);
}
