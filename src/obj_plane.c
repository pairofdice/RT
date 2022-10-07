/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:08:21 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

t_vec3	get_plane_normal(t_context *ctx)
{
	if (vec3_dot(ctx->obj.rot, ctx->ray.dir) > 0)
		return (vec3_neg(ctx->obj.rot));
	return (ctx->obj.rot);
}

/*
Ray and plane intersection
T = Taso = plane.loc
N = Plane normal, plane.rot
P = A point on the plane
R = ray with a start position, R.p, and a direction, R.d.

N • (P - T) = 0
N • P - N • T = 0
and
P = R.p + t * R.d
so
N • (R.p + t * R.d) - N • T = 0
N • (R.p + t * R.d) = N • T
N • R.p + t * (N • R.d) = N • T
t * (N • R.d) = N • T - N • R.p
t = (N • T - N • R.p) /  (N • R.d)
t = (N • (T - R.p)) /  (N • R.d)
*/
int	intersects_plane(t_ray *ray, t_object *plane, double *distance)
{
	double	normal_dot_raydir;
	double	normal_dot_tr;
	t_vec3	tr;

	normal_dot_raydir = vec3_dot(plane->rot, ray->dir);
	tr = vec3_sub(plane->loc, ray->orig);
	normal_dot_tr = vec3_dot(plane->rot, tr);
	if ((normal_dot_tr < 0.0001 && normal_dot_raydir > 0.0)
		|| (normal_dot_tr > 0.0 && normal_dot_raydir < 0.0))
		return (0);
	*distance = normal_dot_tr / normal_dot_raydir;
	return (1);
}
