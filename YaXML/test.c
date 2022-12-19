#include "yaxml.h"

void	print_node(t_xml_node *node, int depth)
{
	int	index = 0;
	int	d_index = 0;
	int	ai = 0;
	char	d[depth];

	if (node != NULL)
	{

	while (d_index < depth)
	{
		d[d_index] = '\t';
		d_index++;
	}
	d[depth] = '\0';
	printf("%s", d);
	printf("TAG = %s DATA = %s\n", node->tag, node->data);
	while (ai < node->attributes.size)
	{
		printf("%s   key = %s value = %s\n", d, node->attributes.list[ai].key, node->attributes.list[ai].value);
		ai++;
	}
	printf("%schildren: %d\n", d, node->children.size);
	while (index < node->children.size)
	{
		print_node(node->children.list[index], depth + 1);
		index++;
	}
	}
}

int	main(void)
{
	t_xml_doc	doc;
	t_xml_node	*main_node;
	int	head = 0;
	int	nodes = 0;
	int	attr = 0;
	
	if (xml_doc_load(&doc, "test.xml"))
	{
		printf("XML Document (version=%s, encoding=%s)\n\n", doc.version, doc.encoding);

		main_node = xml_node_child(doc.head, 0);
		print_node(doc.head, 0);
		xml_doc_free(&doc);
	}
	return (0);
}