/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:09:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/04 15:41:44 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include "objects.h"

t_vec3	new_vec3(void)
{
	t_vec3	v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	return (v);
}

t_object	default_object(void)
{
	t_object	obj;

	obj.type = NOTHING;
	obj.loc = new_vec3();
	obj.rot = new_vec3();
	obj.color = new_vec3();
	obj.brightness = 100.0;
	obj.size = 1.0;
	return (obj);
}

void	rt_sdl_init(t_context *ctx)
{
	ctx->window = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		rt_close(ctx);
	ctx->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI);
	if (ctx->window == NULL)
		rt_close(ctx);
	ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
	if (ctx->renderer == NULL)
		rt_close(ctx);
	ctx->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (ctx->texture == NULL)
		rt_close(ctx);
}

int	init(t_context *ctx)
{
	t_cam	cam;

	ctx->parse_state = NOTHING;
	ctx->obj = default_object();
	ctx->hit = hit_record_new();
	cam.scene_up = (t_point){0.0, 1.0, 0.0};
	ctx->cam = cam;
	rt_sdl_init(ctx);
	ctx->frame_buffer.data = (char *)malloc(WIN_H * WIN_W * 4);
	if (!ctx->frame_buffer.data)
		rt_close(ctx);
	ctx->frame_buffer.texture_data = NULL;
	ctx->quit = FALSE;
	return (1);
}
