/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:32:00 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/18 19:47:18 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_material	material_new(void)
{
	t_material	m;

	m.ambient = 0.2;
	m.diffuse = 0.9;
	m.color = color_new(1, 1, 1);
	m.shininess = 200.0;
	m.specular = 0.9;
	m.pattern.pattern_dif = 0.8;
	m.reflective = 0.0;
	m.pattern.pattern_id = NONE;
	m.pattern.pattern_perlin = FALSE;
	m.normal_disturbance = 0.0;
	return (m);
}
