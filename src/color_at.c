/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:49:39 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/18 12:40:29 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "../include/object.h"

t_color	color_at(t_scene *scene, t_ray *ray)
{
	t_color	color;

	scene_intersect(scene, ray);
	if (ray->xs.vec.len == 0)
		return (color_new(0, 0, 0));
	if (precompute(ray, scene) == 1 || ray->hit.hit_dist > MAX_DISTANCE)
		return (color_new(0, 0, 0));
	color = shade_hit(scene, ray);
	return (color);
}
