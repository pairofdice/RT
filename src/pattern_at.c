/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:22 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/19 16:24:42 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color	pattern_at(t_hit_record hit,
					t_point hit_loc,
					t_color hit_color,
					t_perlin perlin)
{
	double	perlin_out;

	perlin_out = 0;
	if (hit.object->material.pattern.pattern_perlin == TRUE)
		perlin_out = perlin_noice(hit_loc, &perlin);
	if (hit.object->material.pattern.pattern_id == GRID)
		hit_color = pattern_grid(hit_loc, hit_color,
			hit.object->material.pattern.pattern_dif, perlin_out);
	if (hit.object->material.pattern.pattern_id == STRIPED)
	{
		if (pattern_striped(hit_loc.s_xyzw.x + perlin_out) == 1)
		{
			hit_color = tuple_scalar_mult(hit_color,
					hit.object->material.pattern.pattern_dif);
		}
	}
	if (perlin.a)
	{}
	return (hit_color);
}
