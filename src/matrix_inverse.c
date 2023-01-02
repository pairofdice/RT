/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 20:17:12 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_inverse(t_matrix *m)
{
	t_matrix	result;
	double		c;
	t_coords	coords;
	double		det;

	det = matrix_determinant(m);
	result = matrix_new(m->size);
	coords.row = 0;
	while (coords.row < m->size)
	{
		coords.col = 0;
		while (coords.col < m->size)
		{
			c = matrix_cofactor(m, coords.row, coords.col);
			result.rc[coords.col][coords.row] = c / det;
			coords.col++;
		}
		coords.row++;
	}
	return (result);
}
