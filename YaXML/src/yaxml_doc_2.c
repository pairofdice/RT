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

int	xml_error_free(char *buf, char *err_str)
{
	if (err_str != NULL)
	{
		ft_putstr_fd("ERROR: ", 2);
		ft_putendl_fd(err_str, 2);
	}
	free(buf);
	return (FALSE);
}

static int	check_end(const char *str, const char *target)
{
	int	str_len;
	int	target_len;
	int	index[0];

	index[0] = 0;
	str_len = ft_strlen(str);
	target_len = ft_strlen(target);
	printf("\tCHECK END : %d\n\n",target_len);
	if (str_len < target_len)
		return (FALSE);
	while (index[0] < target_len)
	{
		if (str[str_len - target_len + index[0]] != target[index[0]])
			return (FALSE);
	}
	return (TRUE);
}

size_t	get_size(const char *path)
{
	int		fd;
	size_t	size;
	size_t	temp;
	char	buf[4096];

	size = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("ERROR: Could not load file", 2);
		return (FALSE);
	}
	temp = read(fd, buf, 4096);
	while (temp > 0)
	{
		size += temp;
		temp = read(fd, buf, 4096);
	}
	if (close(fd) == -1)
	{
		ft_putendl_fd("ERROR: Couild not close file at get_size", 2);
		return (FALSE);
	}
	return (size);
}

int	read_file(char **buf, const char *path)
{
	int			fd;
	size_t		size;
	char		*temp;

	size = get_size(path);
	if (size == FALSE)
		return (FALSE);
	temp = (char *)malloc(sizeof(temp) * size + 1);
	if (!temp)
		return (xml_error_free(temp, "Buffer malloc failed"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (xml_error_free(temp, "Could not load file"));
	if (read(fd, temp, size) == -1)
		return (xml_error_free(temp, "Could not read file"));
	temp[size] = '\0';
	if (close(fd) == -1)
		return (xml_error_free(temp, "Could not close file at read_file"));
	*buf = temp;
	return (TRUE);
}

int	get_data(t_xml_node *current_node, char *buf, char lex[256])
{
	if (!current_node)
		return (xml_error_free(buf, "Text outside document"));
	if (!current_node->data)
		current_node->data = ft_strdup(lex);
	return (TRUE);
}

int node_end(char *buf, char lex[256], int index[2], t_xml_node **current_node)
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
/*ADD ERROR IF FILE IS DIRECTORY*/
int	xml_doc_load(t_xml_doc *doc, const char *path)
{
	char		*buf = NULL;
	char		lex[256];
	int			index[2];
	t_xml_node	*current_node;
	t_xml_node	*desc;

	index[0] = 0;
	index[1] = 1;
	lex[0] = 0;
	if (!read_file(&buf, path))
		return (FALSE);
	doc->head = xml_node_new(NULL);
	if (doc->head == NULL)
	{
		xml_doc_free(doc);
		return (FALSE);
	}
	current_node = doc->head;
	while (buf[index[0]] != '\0')
	{
		if (buf[index[0]] == '<')
		{
			lex[index[1]] = '\0';
			if (index[1] > 0)
			{
				if (!get_data(current_node, buf, lex))
					return (FALSE);
				index[1] = 0;
			}
			if (buf[index[0] + 1] == '/')
			{
				if (!node_end(buf, lex, index, &current_node))
					return (FALSE);
				continue ;
			}
			// Special nodes - COMMENTS NEED MORE WORK
			if (buf[index[0] + 1] == '!')
			{
				// while loop is problematic. 
				// TODO COMMMENTS ARE BROKEN
				// Doesn't recognize comments if there's no space after <!--
				while (buf[index[0]] != ' ' && buf[index[0]] != '>')
					lex[index[1]++] = buf[index[0]++];
				lex[index[1]] = '\0';
				//comments - This while loop seems kinda stupid, make it better
				printf("I CAN HAZ COMMENT?\n%s\n", lex);
				if (!ft_strcmp(lex, "<!--"))
				{
					while (!check_end(lex, "-->"))
					{
						lex[index[1]++] = buf[index[0]++];
						lex[index[1]] = '\0';
					}
					continue ;
				}
			}
			//declaration tags
			if (buf[index[0] + 1] == '?')
			{
				while (buf[index[0]] != ' ' && buf[index[0]] != '>')
					lex[index[1]++] = buf[index[0]++];
				lex[index[1]] = '\0';
				// This is XML declaration
				if (!ft_strcmp(lex, "<?xml"))
				{
					index[1] = 0;
					desc = xml_node_new(NULL);
					parse_attr(buf, index, lex, desc);
					doc->version = ft_strdup(\
					xml_node_attr_value(desc, "version"));
					doc->encoding = ft_strdup(\
					xml_node_attr_value(desc, "encoding"));
					xml_node_free(desc);
					index[1] = 0;
					index[0]++;
					continue ;
				}
			}
			//set current node
			current_node = xml_node_new(current_node);
			//start tag
			index[0]++;
			if (parse_attr(buf, index, lex, current_node) == TAG_INLINE)
			{
				index[1] = 0;
				current_node = current_node->parent;
				index[0]++;
				continue ;
			}
			//set tag name if none
			lex[index[1]] = '\0';
			if (!current_node->tag)
				current_node->tag = ft_strdup(lex);
			//reset lexer
			index[1] = 0;
			index[0]++;
			continue ;
		}
		else
		{
			lex[index[1]++] = buf[index[0]++];
			//ignore newlines and tabs
			if (lex[index[1] - 1] == '\n' || lex[index[1] - 1] == '\t')
				index[1]--;
		}
	}
	//xml_error_free(buf, "Tis fucked");
	//if (buf != NULL)
	//	free(buf);
	return (TRUE);
}
