/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:28:45 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/19 14:39:15 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_matrix	motion_move(t_matrix orig, t_motion_blur *motion)
{
	t_matrix	new;
	t_tuple		dist;
	double		move_dist;

	move_dist = 0.1;
	dist = tuple_scalar_mult(motion->dir, move_dist);
	new = matrix_translate(dist.s_xyzw.x, dist.s_xyzw.y, dist.s_xyzw.z);
	new = matrix_multiply(&orig, &new);
	motion->speed_iteration += move_dist;
	return (new);
}
