/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:21:08 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/19 14:40:09 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_motion_blur	motion_new(int true_false, double speed, t_tuple dir)
{
	t_motion_blur	new;

	new.on_off = true_false;
	new.speed = speed;
	new.speed_iteration = 0.0;
	new.dir = dir;
	return (new);
}
