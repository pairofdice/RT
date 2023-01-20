/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_record.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/12 17:36:33 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	intersection_record(t_ray *ray, double intersect, t_object *s, \
t_tuple local)
{
	t_intersection	xs;

	xs = intersection_new(intersect, s, local);
	vec_push(&ray->xs.vec, &xs);
}
