/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:51:18 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 17:51:54 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	handle_events(t_context *ctx)
{
	if (ctx->e.key.keysym.sym == SDLK_ESCAPE)
		ctx->quit = TRUE;
	if (ctx->e.key.keysym.sym == SDLK_w)
		move_cam(ctx, ctx->cam.dir);
	if (ctx->e.key.keysym.sym == SDLK_a)
		move_cam(ctx, vec3_neg(ctx->cam.right));
	if (ctx->e.key.keysym.sym == SDLK_s)
		move_cam(ctx, vec3_neg(ctx->cam.dir));
	if (ctx->e.key.keysym.sym == SDLK_d)
		move_cam(ctx, ctx->cam.right);
}
