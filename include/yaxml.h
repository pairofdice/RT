/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:27:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/29 09:27:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YAXML_H
# define YAXML_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

# include "libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef enum e_tag_type
{
	TAG_START,
	TAG_INLINE
}	t_tag_type;

typedef struct s_xml_attribute
{
	char	*key;
	char	*value;
}	t_xml_attr;

typedef struct s_xml_attribute_list
{
	int			memory_size;
	int			size;
	t_xml_attr	*list;
}	t_xml_attrlist;

typedef struct s_xml_node_list
{
	int					memory_size;
	int					size;
	struct s_xml_node	**list;
}	t_xml_nodelist;

typedef struct s_xml_node
{
	char				*tag;
	char				*data;
	struct s_xml_node	*parent;
	t_xml_nodelist		children;
	t_xml_attrlist		attributes;
}	t_xml_node;

typedef struct s_xml_document
{
	t_xml_node	*head;
	char		*version;
	char		*encoding;
}	t_xml_doc;

/* XML doc */
int				xml_doc_load(t_xml_doc *doc, const char *path);

/* Free allocated memory */
void			xml_attr_free(t_xml_attr *attr);
void			xml_nodelist_free(t_xml_nodelist *list);
void			xml_node_free(t_xml_node *node);
void			xml_doc_free(t_xml_doc *doc);

/* node */
t_xml_node		*xml_node_new(t_xml_node *parent);
t_xml_node		*xml_node_child(t_xml_node *parent, int index);
t_xml_nodelist	*xml_node_children(t_xml_node *parent, const char *tag);
char			*xml_node_attr_value(t_xml_node *node, char *key);
t_xml_attr		*xml_node_attr(t_xml_node *node, char *key);
t_xml_node		*xml_node_tag(t_xml_nodelist *list, char *tag);

/* list */
int				xml_attrlist_init(t_xml_attrlist *list);
int				xml_attrlist_add(t_xml_attrlist *list, t_xml_attr *attr);
int				xml_nodelist_init(t_xml_nodelist *list);
int				xml_nodelist_add(t_xml_nodelist *list, t_xml_node *node);
t_xml_node		*xml_nodelist_at(t_xml_nodelist *list, int index);

t_tag_type		parse_attr(char *buf, int index[2], char *lex, \
				t_xml_node *current_node);
#endif