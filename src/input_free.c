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

int	free_lists_fail(t_xml_nodelist **camera, t_xml_nodelist **objects, \
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

int	free_lists(t_xml_nodelist **camera, t_xml_nodelist **objects, \
t_xml_nodelist **lights)
{
	free((*camera)->list);
	free((*objects)->list);
	free((*lights)->list);
	free(*camera);
	free(*objects);
	free(*lights);
	return (TRUE);
}
