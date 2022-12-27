/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:20:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/29 12:20:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaxml.h"

int	xml_get_data(t_xml_node *current_node, t_buffers *buf)
{
	if (!current_node)
		return (xml_error_free(buf, "Text outside document"));
	if (!current_node->data)
		current_node->data = ft_strdup(buf->lex);
	return (TRUE);
}

int	xml_node_end(t_buffers *buf, int index[2], \
t_xml_node **current_node)
{
	index[0] += 2;
	while (buf->mem[index[0]] != '>')
		buf->lex[index[1]++] = buf->mem[index[0]++];
	buf->lex[index[1]] = '\0';
	if (!*current_node)
		return (xml_error_free(buf, "Already at head"));
	if (ft_strcmp((*current_node)->tag, buf->lex))
	{
		ft_putstr_fd((*current_node)->tag, 2);
		ft_putstr_fd(" != ", 2);
		ft_putendl_fd(buf->lex, 2);
		return (xml_error_free(buf, "Mismatched tags"));
	}
	*current_node = (*current_node)->parent;
	index[0]++;
	index[1] = 0;
	return (TRUE);
}

int	xml_init(t_xml_doc *doc, t_buffers *buffer, t_xml_node **current_node, \
int index[2])
{
	doc->head = xml_node_new(NULL);
	if (doc->head == NULL)
	{
		xml_doc_free(doc);
		free(&buffer->mem);
		return (FALSE);
	}
	*current_node = doc->head;
	buffer->lex[0] = 0;
	index[0] = 0;
	index[1] = 0;
	return (TRUE);
}

int	xml_get_content(t_buffers *buf, int index[2], \
t_xml_node **current_node, t_xml_doc *doc)
{
	buf->lex[index[1]] = '\0';
	if (index[1] > 0)
	{
		if (!xml_get_data(*current_node, buf))
			return (FALSE);
		index[1] = 0;
	}
	if (buf->mem[index[0] + 1] == '/')
	{
		if (!xml_node_end(buf, index, current_node))
			return (FALSE);
		return (TRUE);
	}
	if (buf->mem[index[0] + 1] == '!' && xml_comment(buf, &index[0]))
		return (TRUE);
	if (buf->mem[index[0] + 1] == '?' && xml_declaration(buf, index, doc))
		return (TRUE);
	*current_node = xml_node_new(*current_node);
	if (xml_start_tag(buf, index, current_node))
		return (TRUE);
	index[1] = 0;
	index[0]++;
	return (TRUE);
}

int	xml_doc_load(t_xml_doc *doc, const char *path)
{
	t_buffers	buf;
	int			index[2];
	t_xml_node	*curr_node;

	if (!xml_read_file(&buf, path) || !xml_init(doc, &buf, &curr_node, index))
		return (FALSE);
	while (buf.mem[index[0]] != '\0')
	{
		if (buf.mem[index[0]] == '<')
		{
			if (!xml_get_content(&buf, index, &curr_node, doc))
				return (FALSE);
			continue ;
		}
		else
		{
			buf.lex[index[1]++] = buf.mem[index[0]++];
			if (buf.lex[index[1] - 1] == '\n' || buf.lex[index[1] - 1] == '\t')
				index[1]--;
		}
	}
	if (buf.mem != NULL)
		free(buf.mem);
	return (TRUE);
}
