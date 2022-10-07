/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:59:07 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/04 15:41:25 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "vec3.h"

static void	find_normal(t_context *ctx)
{
	ctx->obj = *(t_object *)vec_get(&ctx->scene, (size_t)ctx->hit.closest_id);
	if (ctx->obj.type == SPHERE)
		ctx->hit.normal = get_sphere_normal(ctx);
	else if (ctx->obj.type == PLANE)
		ctx->hit.normal = get_plane_normal(ctx);
	else if (ctx->obj.type == CYLINDER)
		ctx->hit.normal = get_cylinder_normal(ctx);
	else if (ctx->obj.type == CONE)
		ctx->hit.normal = get_cone_normal(ctx);
}

// create a ray for this pixel. origin is the virtual pixel
// on the projection plane
// direction is location of virtual pixel minus location of camera

void	draw_pixel(t_context *ctx, unsigned int x, unsigned int y)
{
	double	distance;

	calc_current_ray(ctx, x, y);
	distance = 1.0 / 0.0;
	intersects(ctx, distance);
	if (ctx->hit.is_hit && ctx->hit.closest_id >= 0)
	{
		find_normal(ctx);
		ctx->hit.light_level = get_light_level((t_ray){vec3_ray_at(ctx->ray,
					ctx->hit.closest_distance), ctx->hit.normal},
				ctx->ray, ctx, ctx->hit.closest_id);
		ctx->hit.color = shade(ctx->obj, ctx->hit.light_level);
		img_pixel_put(&ctx->frame_buffer, x, WIN_H - 1 - y, ctx->hit.color);
	}
	else
		img_pixel_put(&ctx->frame_buffer, x, WIN_H - 1 - y, ctx->ambient.color);
}

void	draw(t_context *ctx)
{
	unsigned int		x;
	unsigned int		y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			draw_pixel(ctx, x, y);
			x++;
		}
		y++;
	}
}

// Copy framebuffer to a texture for SDL to put it to screen
void	write_buffer(t_context *ctx,
					int *texture_data,
					int *texture_pitch)
{
	if (SDL_LockTexture(ctx->texture,
			NULL,
			(void *)&texture_data,
			texture_pitch) == -1)
		rt_close(ctx);
	ft_memcpy(texture_data, ctx->frame_buffer.data, WIN_H * WIN_W * 4);
	SDL_UnlockTexture(ctx->texture);
	if (SDL_RenderCopy(ctx->renderer, ctx->texture, NULL, NULL) == -1)
		rt_close(ctx);
	SDL_RenderPresent(ctx->renderer);
}
