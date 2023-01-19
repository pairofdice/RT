/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:09:50 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/19 16:48:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	vec3_mag(t_vec3 u)
{
	return (sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}

t_vec3	vec3_unit(t_vec3 u)
{
	double	mag;

	mag = vec3_mag(u);
	return ((t_vec3){u.x / mag, u.y / mag, u.z / mag});
}

t_vec3	vec3_scalar_mult(t_vec3 u, double x)
{
	return ((t_vec3){u.x * x, u.y * x, u.z * x});
}

t_vec3	vec3_neg(t_vec3 u)
{
	return ((t_vec3){-u.x, -u.y, -u.z});
}
