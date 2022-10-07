/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:53:37 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 17:46:23 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	move_cam(t_context *ctx, t_vec3 dir)
{
	t_point	loc;

	loc = ctx->cam.loc;
	loc = vec3_add(loc, dir);
	init_camera(&ctx->cam, loc);
	draw(ctx);
	write_buffer(ctx,
		ctx->frame_buffer.texture_data,
		&ctx->frame_buffer.texture_pitch);
}

// Sets up the virtual screen from camera location, center of interest
// and scene up direction (assumed to be positive y).
// Virtual screen (projection plane)is a small offset away from camera pivot.
// First we build the direction vectors of the camera with vector cross product
// Then we set the center of the projection plane and the lower left anchor
void	init_camera(t_cam *cam, t_point loc)
{
	cam->loc = loc;
	cam->distance_to_proj = 0.1;
	cam->aspect = (float)WIN_W / WIN_H;
	cam->projection_plane_h = tan(1.05 / 2) * 2 * cam->distance_to_proj;
	cam->projection_plane_w = cam->projection_plane_h * cam->aspect;
	cam->dir = vec3_unit(vec3_sub(cam->coi, cam->loc));
	cam->n = vec3_neg(cam->dir);
	cam->right = vec3_cross(cam->scene_up, cam->n);
	cam->up = vec3_cross(cam->n, cam->right);
	cam->projection_plane_center = vec3_add(cam->loc,
			vec3_scalar_mult(cam->dir, cam->distance_to_proj));
	cam->cam_to_proj = vec3_sub(cam->loc, cam->projection_plane_center);
	cam->virtual_screen_anchor = vec3_sub(cam->projection_plane_center,
			vec3_scalar_mult(cam->right,
				0.5 * cam->projection_plane_w));
	cam->virtual_screen_anchor = vec3_sub(cam->virtual_screen_anchor,
			vec3_scalar_mult(cam->up,
				0.5 * cam->projection_plane_h));
}

void	set_camera(t_context *ctx)
{
	ctx->cam.coi = ctx->obj.coi;
	ctx->cam.loc = ctx->obj.loc;
	init_camera(&ctx->cam, ctx->obj.loc);
}
