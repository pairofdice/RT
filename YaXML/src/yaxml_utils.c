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

int	xml_comment(const char *buf, int *index)
{
	int	temp;

	temp = *index;
	if (buf[temp + 2] == '\0' || buf[temp + 3] == '\0' || \
		buf[temp + 2] != '-' || buf[temp + 3] != '-')
		return (FALSE);
	while (buf[temp] != '\0')
	{
		while (buf[temp] != '\0' && buf[temp] != '>')
			(temp)++;
		if (buf[temp] == '\0')
			return (FALSE);
		else if (buf[temp] == '>' && buf[temp - 1] == '-' && \
		buf[temp - 2] == '-')
		{
			*index = ++temp;
			return (TRUE);
		}
		else
			(temp)++;
	}
	return (FALSE);
}

int	xml_declaration(const char *buf, int *index, t_xml_doc *doc)
{
	t_xml_node	*desc;
	char		lex[1024];

	while (buf[index[0]] != '\0' && buf[index[0]] != ' ' && \
	buf[index[0]] != '>')
		lex[index[1]++] = buf[index[0]++];
	lex[index[1]] = '\0';
	if (!ft_strcmp(lex, "<?xml"))
	{
		index[1] = 0;
		desc = xml_node_new(NULL);
		xml_parse_attr(buf, index, lex, desc);
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

int	xml_start_tag(const char *buf, int index[2], char *lex, t_xml_node **node)
{
	index[0]++;
	if (xml_parse_attr(buf, index, lex, *node) == TAG_INLINE)
	{
		index[1] = 0;
		*node = (*node)->parent;
		index[0]++;
		return (TRUE);
	}
	lex[index[1]] = '\0';
	if (!(*node)->tag)
		(*node)->tag = ft_strdup(lex);
	return (FALSE);
}
