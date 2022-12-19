/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_light_and_camera.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:26:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/13 13:36:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "yaxml.h"

t_color	color_new_2(t_tuple tuple)
{
	return(color_new(tuple.a[0], tuple.a[1], tuple.a[2]));
}

t_point	point_new_2(t_tuple tuple)
{
	return(point_new(tuple.a[0], tuple.a[1], tuple.a[2]));
}

/*TODO CLEANUP?*/
int	get_light(t_xml_node *node, t_light *light)
{
	t_xml_node	*temp;

	temp = xml_node_tag(&node->children, "pos");
	if (temp == NULL)
	{
		ft_putendl_fd("ERROR: No [pos] info for light", 2);
		return (FALSE);
	}
	get_tuple(&light->location, temp->data);
	temp = xml_node_tag(&node->children, "color");
	if (temp == NULL)
	{
		ft_putendl_fd("ERROR: No [color] info for light", 2);
		return (FALSE);
	}
	get_tuple(&light->intensity, temp->data);
	light->intensity = color_new_2(light->intensity);
	light->location = point_new_2(light->location);
	return (TRUE);
}

int	get_camera(t_xml_node *node, t_cam *cam)
{
	t_xml_node	*temp;
	int			index;

	index = 0;
	while (index < node->children.size)
	{
		temp = node->children.list[index];
		if (!ft_strcmp(temp->tag, "pos"))
			get_tuple(&cam->pos, temp->data);
		else if (!ft_strcmp(temp->tag, "coi"))
			get_tuple(&cam->coi, temp->data);
		else if (!ft_strcmp(temp->tag, "v_up"))
			get_tuple(&cam->v_up, temp->data);
		index++;
	}
	return (TRUE);
}
