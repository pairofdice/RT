/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:33:14 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/13 13:33:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "rt.h"
# include "yaxml.h"
# include <math.h>

t_matrix	matrix_translate_2(t_tuple tuple);
double		get_double(char *str);
void		get_tuple(t_tuple *tuple, char *str);
int			get_material(t_xml_node *node, t_material *mat);
int			get_light(t_xml_node *node, t_light *light);
int			get_camera(t_xml_node *node, t_cam *cam);
int			get_details(t_xml_node *node, t_object *obj);
int			get_obj_details(t_xml_node *node, t_object *obj);
int			get_object(t_xml_node *node, t_object *obj);
int			prepare_objects(t_xml_nodelist *list, t_vec *obj);
int			prepare_camera(t_xml_nodelist *list, t_cam *cam);
int			prepare_lights(t_xml_nodelist *list, t_vec *light);
int			read_xml(t_xml_doc *doc, t_main *main);

#endif
