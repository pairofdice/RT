/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:46:34 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/04 15:41:58 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	rt_close(t_context *ctx)
{
	vec_free(&ctx->scene);
	ft_memdel((void **)&ctx->frame_buffer.data);
	SDL_DestroyWindow(ctx->window);
	ctx->window = NULL;
	SDL_DestroyTexture(ctx->texture);
	ctx->texture = NULL;
	SDL_DestroyRenderer(ctx->renderer);
	ctx->window = NULL;
	SDL_Quit();
	exit(0);
}

void	rt_run(t_context *ctx)
{
	while (!ctx->quit)
	{
		if (SDL_WaitEvent(&ctx->e) != 0)
		{
			if (ctx->e.type == SDL_QUIT)
				ctx->quit = TRUE;
			else if (ctx->e.type == SDL_WINDOWEVENT)
			{
				if (ctx->e.window.event == SDL_WINDOWEVENT_EXPOSED)
					write_buffer(ctx,
						ctx->frame_buffer.texture_data,
						&ctx->frame_buffer.texture_pitch);
			}
			else if (ctx->e.type == SDL_KEYDOWN)
				handle_events(ctx);
		}
	}
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	init(&ctx);
	handle_args(argc, argv, &ctx);
	draw(&ctx);
	rt_run(&ctx);
	rt_close(&ctx);
	return (0);
}
