/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:57:35 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/14 18:49:07 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	scene_new(t_scene *scene)
{
	if (!vec_new(&scene->lights, 6, sizeof(t_light)))
		return (1);
	if (!vec_new(&scene->objects, 6, sizeof(t_object)))
		return (1);
	scene->cam.max_reflections = DEFAULT_MAX_REFLECTIONS;
	scene->glare_toggle = FALSE;
	load_perlin_data(&scene->perlin);
	return (0);
}
