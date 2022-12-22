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

int	xml_get_data(t_xml_node *current_node, char *buf, char lex[256])
{
	if (!current_node)
		return (xml_error_free(buf, "Text outside document"));
	if (!current_node->data)
		current_node->data = ft_strdup(lex);
	return (TRUE);
}

int	xml_node_end(char *buf, char lex[256], int index[2], \
t_xml_node **current_node)
{
	index[0] += 2;
	while (buf[index[0]] != '>')
		lex[index[1]++] = buf[index[0]++];
	lex[index[1]] = '\0';
	if (!*current_node)
		return (xml_error_free(buf, "Already at head"));
	if (ft_strcmp((*current_node)->tag, lex))
	{
		ft_putstr_fd((*current_node)->tag, 2);
		ft_putstr_fd(" != ", 2);
		ft_putendl_fd(lex, 2);
		return (xml_error_free(buf, "Mismatched tags"));
	}
	*current_node = (*current_node)->parent;
	index[0]++;
	index[1] = 0;
	return (TRUE);
}

int	xml_init_doc(t_xml_doc *doc, t_buffer *buffer, t_xml_node **current_node)
{
	doc->head = xml_node_new(NULL);
	if (doc->head == NULL)
	{
		xml_doc_free(doc);
		free(buffer->mem);
		return (FALSE);
	}
	*current_node = doc->head;
	return (TRUE);
}

int	xml_doc_load(t_xml_doc *doc, const char *path)
{
	t_buffer	buffer;
	char		*buf;
	char		lex[1024];
	int			index[2];
	t_xml_node	*current_node;

	index[0] = 0;
	index[1] = 1;
	lex[0] = 0;
	if (!xml_read_file(&buffer, path))
		return (FALSE);
	if (!xml_init_doc(doc, &buffer, &current_node))
		return (FALSE);
	buf = buffer.mem;
	while (buf[index[0]] != '\0')
	{
		if (buf[index[0]] == '<')
		{
			lex[index[1]] = '\0';
			if (index[1] > 0)
			{
				if (!xml_get_data(current_node, buf, lex))
					return (FALSE);
				index[1] = 0;
			}
			if (buf[index[0] + 1] == '/')
			{
				if (!xml_node_end(buf, lex, index, &current_node))
					return (FALSE);
				continue ;
			}
			if (buf[index[0] + 1] == '!')
			{
				if (xml_comment(buf, &index[0]))
					continue ;
			}
			if (buf[index[0] + 1] == '?')
			{
				if (xml_declaration(buf, index, doc))
					continue ;
			}
			current_node = xml_node_new(current_node);
			if (xml_start_tag(buf, index, lex, &current_node))
				continue ;
			index[1] = 0;
			index[0]++;
			continue ;
		}
		else
		{
			lex[index[1]++] = buf[index[0]++];
			if (lex[index[1] - 1] == '\n' || lex[index[1] - 1] == '\t')
				index[1]--;
		}
	}
	if (buf != NULL)
		free(buf);
	return (TRUE);
}
