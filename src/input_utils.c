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

int	free_lists(	t_xml_nodelist **camera, t_xml_nodelist **objects, \
t_xml_nodelist **lights, t_main *main)
{
	free((*camera)->list);
	free((*objects)->list);
	free((*lights)->list);
	free(*camera);
	free(*objects);
	free(*lights);
	vec_free(&main->scene.lights);
	vec_free(&main->scene.objects);
	return (FALSE);
}

int	read_xml(t_xml_doc *doc, t_main *main)
{
	t_xml_nodelist	*camera;
	t_xml_nodelist	*objects;
	t_xml_nodelist	*lights;

	doc->version = NULL;
	doc->encoding = NULL;
	scene_new(&main->scene);
	load_perlin_data(&main->scene.perlin);
	camera = xml_node_children(doc->head, "camera");
	objects = xml_node_children(doc->head, "object");
	lights = xml_node_children(doc->head, "light");
	if (!prepare_camera(camera, &main->scene.cam))
		return (free_lists(&camera, &objects, &lights, main));
	if (!prepare_objects(objects, &main->scene.objects))
		return (free_lists(&camera, &objects, &lights, main));
	if (!prepare_lights(lights, &main->scene.lights))
		return (free_lists(&camera, &objects, &lights, main));
	free(camera->list);
	free(objects->list);
	free(lights->list);
	free(camera);
	free(objects);
	free(lights);
	return (TRUE);
}
