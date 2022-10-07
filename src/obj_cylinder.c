/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:24:39 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:06:24 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

t_abc static	calc_abc_cylinder(t_ray ray,
									t_vec3 cyldir,
									t_vec3 raycyl,
									double radius)
{
	t_abc	abc;

	abc.a = 1 - vec3_dot(ray.dir, cyldir) * vec3_dot(ray.dir, cyldir);
	abc.b = 2 * (vec3_dot(ray.dir, raycyl) - vec3_dot(ray.dir, cyldir)
			* vec3_dot(raycyl, cyldir));
	abc.c = vec3_dot(raycyl, raycyl) - vec3_dot(raycyl, cyldir)
		* vec3_dot(raycyl, cyldir) - radius * radius;
	return (abc);
}

t_vec3	get_cylinder_normal(t_context *ctx)
{
	t_vec3	result;
	t_vec3	hit_loc;
	t_vec3	hypotenuse;
	t_vec3	hit_along_cyldir;

	hit_loc = vec3_ray_at(ctx->ray, ctx->hit.closest_distance);
	hypotenuse = vec3_sub(hit_loc, ctx->obj.loc);
	hit_along_cyldir = vec3_ray_at((t_ray){ctx->obj.loc,
			ctx->obj.rot},
			vec3_dot(hypotenuse, ctx->obj.rot));
	result = vec3_sub(hit_loc, hit_along_cyldir);
	return (result);
}

int	intersects_cylinder(t_ray *ray, t_object *cylinder, double *distance)
{
	t_vec3	ray_cyl;
	t_abc	abc;
	double	b2_4ac;

	ray_cyl = vec3_sub(ray->orig, cylinder->loc);
	abc = calc_abc_cylinder(*ray, cylinder->rot, ray_cyl, cylinder->size);
	b2_4ac = calc_b2_4ac(abc);
	if (b2_4ac <= 0)
		return (0);
	*distance = quadratic(abc, b2_4ac);
	if (*distance < 0)
		return (0);
	return (1);
}
