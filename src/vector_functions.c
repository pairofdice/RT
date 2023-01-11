/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:55:00 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/07 16:57:07 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	t_vec3	new;
	double	ret;

	new.x = a.x * b.x;
	new.y = a.y * b.y;
	new.z = a.z * b.z;
	ret = (new.x + new.y + new.z);
	return (ret);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_vec3	multiply_vectors(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	new.x = a.x * b.x;
	new.y = a.y * b.y;
	new.z = a.z * b.z;
	return (new);
}
