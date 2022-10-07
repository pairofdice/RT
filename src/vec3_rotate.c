/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:14:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 15:50:29 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

static void	sf_vec_rotate_x(t_vec3 *v, double deg)
{
	t_vec3	temp;
	double	rad;

	rad = to_radians(deg);
	temp.z = v->z;
	temp.y = v->y;
	v->z = temp.z * cos(rad) - temp.y * sin(rad);
	v->y = temp.z * sin(rad) + temp.y * cos(rad);
}

static void	sf_vec_rotate_y(t_vec3 *v, double deg)
{
	t_vec3	temp;
	double	rad;

	rad = to_radians(deg);
	temp.x = v->x;
	temp.z = v->z;
	v->x = temp.x * cos(rad) - temp.z * sin(rad);
	v->z = temp.x * sin(rad) + temp.z * cos(rad);
}

static void	sf_vec_rotate_z(t_vec3 *v, double deg)
{
	t_vec3	temp;
	double	rad;

	rad = to_radians(deg);
	temp.y = v->y;
	temp.x = v->x;
	v->y = temp.y * cos(rad) - temp.x * sin(rad);
	v->x = temp.y * sin(rad) + temp.x * cos(rad);
}

t_vec3	vec3_rotate(t_vec3 dir, t_vec3 rot)
{
	t_vec3	result;

	result = dir;
	sf_vec_rotate_x(&result, rot.x);
	sf_vec_rotate_y(&result, rot.y);
	sf_vec_rotate_z(&result, rot.z);
	return (result);
}
