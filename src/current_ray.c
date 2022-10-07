/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:22:54 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/30 15:16:14 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	calc_current_ray(t_context *ctx, unsigned int x, unsigned int y)
{
	ctx->ray.orig = vec3_add(ctx->cam.virtual_screen_anchor,
			vec3_scalar_mult(ctx->cam.right,
				x * ctx->cam.projection_plane_w / WIN_W));
	ctx->ray.orig = vec3_add(ctx->ray.orig, vec3_scalar_mult(ctx->cam.up,
				y * ctx->cam.projection_plane_h / WIN_H));
	ctx->ray.dir = vec3_sub(ctx->ray.orig, ctx->cam.loc);
	ctx->ray.dir = vec3_unit(ctx->ray.dir);
}
