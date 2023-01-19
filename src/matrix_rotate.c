/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:35:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

t_matrix	matrix_rotate_x(double w)
{
	t_matrix	transform;

	transform = matrix_new_identity(4);
	transform.rc[1][1] = cos(w);
	transform.rc[2][2] = cos(w);
	transform.rc[1][2] = -sin(w);
	transform.rc[2][1] = sin(w);
	return (transform);
}

t_matrix	matrix_rotate_y(double w)
{
	t_matrix	transform;

	transform = matrix_new_identity(4);
	transform.rc[0][0] = cos(w);
	transform.rc[0][2] = sin(w);
	transform.rc[2][0] = -sin(w);
	transform.rc[2][2] = cos(w);
	return (transform);
}

t_matrix	matrix_rotate_z(double w)
{
	t_matrix	transform;

	transform = matrix_new_identity(4);
	transform.rc[0][0] = cos(w);
	transform.rc[1][1] = cos(w);
	transform.rc[0][1] = -sin(w);
	transform.rc[1][0] = sin(w);
	return (transform);
}
