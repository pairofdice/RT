/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:28:45 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/02 14:34:15 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_matrix	motion_move(t_matrix orig, t_motion_blur *motion)
{
	t_matrix	new;

	new = matrix_multiply(&orig, &motion->transform);
	motion->speed_iteration += 0.1;
	return (new);
}
