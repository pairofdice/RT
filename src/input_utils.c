/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/13 13:36:14 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

t_matrix	matrix_translate_2(t_tuple tuple)
{
	return (matrix_translate(tuple.a[0], tuple.a[1], tuple.a[2]));
}

double	get_double(char *str)
{
	double	negative;
	double	num;
	int		len;

	negative = 1.0f;
	num = 0.0;
	len = 0;
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '-')
	{
		negative = -1.0f;
		str++;
	}
	num = (double)ft_atoi(str);
	while (*str != '\0' && *str++ != '.')
		;
	while (str[len] != '\0' && ft_isdigit(str[len]))
		len++;
	if (len)
	{
		num += (double)(ft_atoi(str) / powf(10, len));
	}
	return (num * negative);
}

void	get_tuple(t_tuple *tuple, char *str)
{
	int	index;
	int	index_t;

	index = 0;
	index_t = 0;
	while (str[index] != '\0')
	{
		if (str[index] == ' ' && str[index + 1] != '\0')
		{
			tuple->a[index_t++] = get_double(&str[index + 1]);
		}
		index++;
	}
}

void	get_settings(t_xml_node *scene, t_main *main)
{
	char		*str;
	t_xml_node	*node;

	node = xml_node_tag(&scene->children, "settings");
	main->settings.edge_detection_presission = EDGE_DETECTION_PRECISION;
	main->settings.orig_ant_al = DEFAULT_ANTIALIAS;
	main->scene.cam.max_reflections = DEFAULT_MAX_REFLECTIONS;
	if (node != NULL)
	{
		str = xml_node_attr_value(scene, "stereoscopy");
		if (str != NULL && !ft_strcmp(str, "true"))
			main->sdl.stereocopy = TRUE;
		str = xml_node_attr_value(node, "edge_detection_precision");
		if (str != NULL)
			main->settings.edge_detection_presission = ft_atof(str);
		str = xml_node_attr_value(node, "ant_al");
		if (str != NULL)
			main->settings.orig_ant_al = int_clamp(ft_atoi(str), 1, 6);
		str = xml_node_attr_value(node, "max_reflections");
		if (str != NULL)
			main->scene.cam.max_reflections = int_clamp(ft_atoi(str), 1, 20);
	}
}

int	read_xml(t_xml_doc *doc, t_main *main)
{
	t_xml_node		*scene;
	t_xml_nodelist	*nodelist;

	nodelist = NULL;
	scene = xml_node_tag(&doc->head->children, "scene");
	if (scene)
	{
		get_settings(scene, main);
		nodelist = xml_node_children(scene, "camera");
		if (!prepare_camera(nodelist, &main->scene.cam))
			return (free_lists_fail(&nodelist, main));
		free_lists(&nodelist);
		nodelist = xml_node_children(scene, "object");
		if (!prepare_objects(nodelist, &main->scene.objects))
			return (free_lists_fail(&nodelist, main));
		free_lists(&nodelist);
		nodelist = xml_node_children(scene, "light");
		if (!prepare_lights(nodelist, &main->scene.lights))
			return (free_lists_fail(&nodelist, main));
		return (free_lists(&nodelist));
	}
	return (return_error("ERROR: No scene in file"));
}
