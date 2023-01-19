/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glare.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:41:59 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 14:17:05 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color	glare(t_ray *ray, t_vec *lights)
{
	t_color	glare;
	t_light	light;
	size_t	i;
	double	dot;
	
	glare = color_new(0, 0, 0);
	i = 0;
	while (i < lights->len)
	{
		light = *(t_light *)vec_get(lights, i);
		dot = vector_dot(tuple_neg(light.direction), tuple_unit(ray->dir));
		if (dot > 0.99)
		{
			glare = tuple_add(glare, color_new(1, 1, 1));
		}
		i++;
	}
	return (glare);
}