/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/15 14:15:08 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_intersection	intersection_new(double time, t_object *o, t_tuple local)
{
	t_intersection	xs;

	xs.t = time;
	xs.object = o;
	xs.i = o->id;
	xs.local = local;
	return (xs);
}
