/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:16:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/16 14:39:57 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_intersection	find_closest_intersection(t_intersections *xs)
{
	t_intersection	closest;
	size_t			i;
	t_intersection	t;

	i = 0;
	closest.t = INFINITY;
	while (i < xs->vec.len)
	{
		t = *(t_intersection *)vec_get(&xs->vec, i);
		if (t.object != NULL && t.t < closest.t && t.t >= 0)
		{
			closest = t;
			closest.object = t.object;
			closest.i = t.object->id;
		}
		i++;
	}
	return (closest);
}
