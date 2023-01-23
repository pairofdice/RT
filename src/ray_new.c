/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:47:15 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	new_intersections(t_vec *intersections)
{
	return (vec_new(intersections, 4, sizeof(t_intersection)));
}

t_ray	ray_new(t_point origin, t_vector dir)
{
	t_ray	result;

	result.orig = origin;
	result.dir = dir;
	result.hit.neg_hit = FALSE;
	new_intersections(&result.xs.vec);
	return (result);
}

t_ray	ray_new_no_malloc(t_point origin, t_vector dir)
{
	t_ray	result;

	result.orig = origin;
	result.dir = dir;
	return (result);
}
