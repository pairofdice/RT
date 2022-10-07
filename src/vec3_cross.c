/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:14:47 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/09 20:01:32 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_cross(t_vec3 u, t_vec3 v)
{
	t_vec3	crossed;

	crossed.x = u.y * v.z - u.z * v.y;
	crossed.y = u.z * v.x - u.x * v.z;
	crossed.z = u.x * v.y - u.y * v.x;
	return (crossed);
}
