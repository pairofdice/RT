/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_detection_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:26:51 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/05 12:30:20 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Edge_detection_check checks the coordinates of the image and if it's
**	in the image it returns a color.
**	It also adds count if it is inside the camerafor for future calculations.
*/

double	edge_detection_check(int x, int y, int *count, int *image)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		*count += 1;
		return ((((image[(y * WIN_W) + x]) >> 24 & 255) / 255.0));
	}
	return (0.0);
}
