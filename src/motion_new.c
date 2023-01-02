/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:21:08 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/02 15:32:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_motion_blur	motion_new(int true_false, double speed, t_tuple dir)
{
	t_motion_blur	new;
	t_tuple			dist;

	new.on_off = true_false;
	if (speed > MAX_SPEED)
		new.speed = MAX_SPEED;
	else
		new.speed = speed;
	new.speed_iteration = 0.0;
	new.dir = tuple_unit(dir);
	dist = tuple_scalar_mult(dir, 0.1);
	new.transform = matrix_translate(dist.s_xyzw.x, dist.s_xyzw.y, dist.s_xyzw.z);
	return (new);
}
