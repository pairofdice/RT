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

void	*xml_resize_memory(void *ptr, size_t size, size_t old_size)
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

int	xml_comment(t_buffers*buf, int *index)
{
	int	temp;

	temp = *index;
	if (buf->mem[temp + 2] == '\0' || buf->mem[temp + 3] == '\0' || \
		buf->mem[temp + 2] != '-' || buf->mem[temp + 3] != '-')
		return (FALSE);
	while (buf->mem[temp] != '\0')
	{
		while (buf->mem[temp] != '\0' && buf->mem[temp] != '>')
			(temp)++;
		if (buf->mem[temp] == '\0')
			return (FALSE);
		else if (buf->mem[temp] == '>' && buf->mem[temp - 1] == '-' && \
		buf->mem[temp - 2] == '-')
		{
			*index = ++temp;
			return (TRUE);
		}
		else
			(temp)++;
	}
	return (FALSE);
}

int	xml_declaration(t_buffers *buf, int *index, t_xml_doc *doc)
{
	t_xml_node	*desc;

	while (buf->mem[index[0]] != '\0' && buf->mem[index[0]] != ' ' && \
	buf->mem[index[0]] != '>')
		buf->lex[index[1]++] = buf->mem[index[0]++];
	buf->lex[index[1]] = '\0';
	if (!ft_strcmp(buf->lex, "<?xml"))
	{
		index[1] = 0;
		desc = xml_node_new(NULL);
		xml_parse_attr(buf, index, desc);
		doc->version = ft_strdup(\
		xml_node_attr_value(desc, "version"));
		doc->encoding = ft_strdup(\
		xml_node_attr_value(desc, "encoding"));
		xml_node_free(desc);
		index[1] = 0;
		index[0]++;
		return (TRUE);
	}
	return (FALSE);
}

int	xml_start_tag(t_buffers *buf, int index[2], t_xml_node **node)
{
	index[0]++;
	if (xml_parse_attr(buf, index, *node) == TAG_INLINE)
	{
		index[1] = 0;
		*node = (*node)->parent;
		index[0]++;
		return (TRUE);
	}
	buf->lex[index[1]] = '\0';
	if (!(*node)->tag)
		(*node)->tag = ft_strdup(buf->lex);
	return (FALSE);
}
