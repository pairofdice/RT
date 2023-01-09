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
	main->settings.edge_detection_presission = 0.02;
	main->settings.orig_ant_al = 6;
	if (node != NULL)
	{
		str = xml_node_attr_value(scene, "stereoscopy");
		if (str != NULL && !ft_strcmp(str, "TRUE"))
			main->sdl.stereocopy = TRUE;
		str = xml_node_attr_value(node, "edge_detection_precision");
		if (str != NULL)
			main->settings.edge_detection_presission = ft_atof(str);
		str = xml_node_attr_value(node, "ant_al");
		if (str != NULL)
			main->settings.orig_ant_al = ft_atof(str);
	}
}

int	read_xml(t_xml_doc *doc, t_main *main)
{
	t_xml_node		*scene;
	t_xml_nodelist	*camera;
	t_xml_nodelist	*objects;
	t_xml_nodelist	*lights;

	scene = xml_node_tag(&doc->head->children, "scene");
	if (scene)
	{
		get_settings(scene, main);
		camera = xml_node_children(scene, "camera");
		if (!prepare_camera(camera, &main->scene.cam))
			return (free_lists_fail(&camera, &objects, &lights, main));
		objects = xml_node_children(scene, "object");
		if (!prepare_objects(objects, &main->scene.objects))
			return (free_lists_fail(&camera, &objects, &lights, main));
		lights = xml_node_children(scene, "light");
		if (!prepare_lights(lights, &main->scene.lights))
			return (free_lists_fail(&camera, &objects, &lights, main));
		return (free_lists(&camera, &objects, &lights));
	}
	return (return_error("ERROR: No scene in file"));
}
