/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_submatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/16 15:47:32 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_submatrix(t_matrix *src, t_coords skip)
{
	t_coords	c;
	t_coords	padding;
	t_matrix	result;

	result = matrix_new(src->size - 1);
	if (src->size == 3 || src->size == 4)
	{
		c.row = 0;
		while (c.row < result.size)
		{
			padding.row = (c.row >= skip.row);
			c.col = 0;
			while (c.col < result.size)
			{
				padding.col = (c.col >= skip.col);
				result.rc[c.row][c.col] = src->rc[c.row + padding.row][c.col
					+ padding.col];
				c.col++;
			}
			c.row++;
		}
	}
	return (result);
}
