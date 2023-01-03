/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_detection_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:26:51 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/03 12:39:32 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	edge_detection_check(int x, int y, int *count, int *image)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		*count += 1;
		return ((((image[(y * WIN_W) + x]) >> 24 & 255) / 255.0));
	}
	return (0.0);
}
