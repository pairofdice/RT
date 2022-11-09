/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/09 17:32:31 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

//Copys 1d arrey to texture and draws it.

void	draw_filter(t_sdl *sdl, int *filter_type, int i)
{
	if (i == 1)
	{
		if (sdl->event.key.keysym.sym == SDLK_DOWN && *filter_type > 0)
			*filter_type -= 1;
		else if (sdl->event.key.keysym.sym == SDLK_DOWN)
			*filter_type = 4;
		else if (sdl->event.key.keysym.sym == SDLK_UP && *filter_type < 4)
			*filter_type += 1;
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = SPHERE;
	}
	if (*filter_type == 0)
		draw_to_window(sdl, sdl->frame_buffer.data);
	else if (*filter_type == 1)
		draw_to_window(sdl, sdl->frame_buffer.cartoon);
	else if (*filter_type == 2)
		draw_to_window(sdl, sdl->frame_buffer.b_w);
	else if (*filter_type == 3)
		draw_to_window(sdl, sdl->frame_buffer.b_w_cartoon);
	else if (*filter_type == 4)
		draw_to_window(sdl, sdl->frame_buffer.edge_map);
}

static void	free_buffers_and_sdl(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyWindow(sdl->win);
	free(sdl->frame_buffer.data);
	free(sdl->frame_buffer.cartoon);
	free(sdl->frame_buffer.b_w);
	free(sdl->frame_buffer.b_w_cartoon);
	free(sdl->frame_buffer.edge_map);
}

// Infinite loop to handle the window.

void	rt_loop_and_exit(t_sdl *sdl)
{
	int	quit;
	int	filter_type;

	quit = 0;
	filter_type = SPHERE;
	while (quit == 0)
	{
		if (SDL_WaitEvent(&sdl->event) != 0)
			kay_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type, 0);
	}
	free_buffers_and_sdl(sdl);
}

int	tests(void); // unit tests

int	main(void)
{
	t_main	main;

	tests();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (initialize_window(&main) == 0)
		return (1);
	main.cam.pos.x = 0.0;
	main.cam.pos.y = 0.0;
	main.cam.pos.z = 0.0;
	
	main.cam.v_up.x = 0.0;
	main.cam.v_up.y = 1.0;
	main.cam.v_up.z = 0.0;
	
	main.cam.coi.x = 0.0;
	main.cam.coi.y = 0.0;
	main.cam.coi.z = 10.0;

	main.light.pos.x = 10.0;
	main.light.pos.y = 0.0;
	main.light.pos.z = 0.0;

	main.obj[0].loc.x = 0.0;
	main.obj[0].loc.y = 0.0;
	main.obj[0].loc.z = 30.0;
	main.obj[0].size = 3.0;
	main.obj[0].type = SPHERE;
	main.obj[0].color.s_rgb.r = 0.0;
	main.obj[0].color.s_rgb.g = 1.0;
	main.obj[0].color.s_rgb.b = 0.0;
	
	main.obj[1].loc.x = 5.0;
	main.obj[1].loc.y = 0.0;
	main.obj[1].loc.z = 30.0;
	main.obj[1].size = 0.1;
	main.obj[1].type = SPHERE;
	main.obj[1].color.s_rgb.r = 1.0;
	main.obj[1].color.s_rgb.g = 0.0;
	main.obj[1].color.s_rgb.b = 0.0;

	main.obj[2].loc.x = 0.0;
	main.obj[2].loc.y = 0.0;
	main.obj[2].loc.z = 40.0;
	main.obj[2].rot.x = 0.0;
	main.obj[2].rot.y = 0.0;
	main.obj[2].rot.z = 1.0;
	main.obj[2].type = PLANE;
	main.obj[2].color.s_rgb.r = 1.0;
	main.obj[2].color.s_rgb.g = 1.0;
	main.obj[2].color.s_rgb.b = 1.0;

	main.obj[3].loc.x = 0.0;
	main.obj[3].loc.y = -10.0;
	main.obj[3].loc.z = 40.0;
	main.obj[3].rot.x = 0.0;
	main.obj[3].rot.y = 1.0;
	main.obj[3].rot.z = 0.0;
	main.obj[3].type = PLANE;
	main.obj[3].color.s_rgb.r = 0.0;
	main.obj[3].color.s_rgb.g = 1.0;
	main.obj[3].color.s_rgb.b = 1.0;
		
	main.obj[4].loc.x = 0.0;
	main.obj[4].loc.y = 0.0;
	main.obj[4].loc.z = 30.0;
	main.obj[4].rot.x = 1.0;
	main.obj[4].rot.y = 1.0;
	main.obj[4].rot.z = 1.0;
	main.obj[4].type = CYLINDER;
	main.obj[4].size = 1;
	main.obj[4].color.s_rgb.r = 1.0;
	main.obj[4].color.s_rgb.g = 1.0;
	main.obj[4].color.s_rgb.b = 1.0;

	main.obj[5].loc.x = 0.0;
	main.obj[5].loc.y = 0.0;
	main.obj[5].loc.z = 30.0;
	main.obj[5].rot.x = -1.0;
	main.obj[5].rot.y = 1.0;
	main.obj[5].rot.z = 1.0;
	main.obj[5].type = CYLINDER;
	main.obj[5].size = 0.5;
	main.obj[5].color.s_rgb.r = 1.0;
	main.obj[5].color.s_rgb.g = 0.0;
	main.obj[5].color.s_rgb.b = 1.0;

	main.obj[6].loc.x = -10.0;
	main.obj[6].loc.y = 0.0;
	main.obj[6].loc.z = 30.0;
	main.obj[6].rot.x = 0.0;
	main.obj[6].rot.y = 1.0;
	main.obj[6].rot.z = 0.0;
	main.obj[6].type = CONE;
	main.obj[6].size = 1;
	main.obj[6].color.s_rgb.r = 1.0;
	main.obj[6].color.s_rgb.g = 0.1;
	main.obj[6].color.s_rgb.b = 0.8;
	main.obj_count = 7;
	
	initialize_camera(&main.cam);
	create_threads(&main, 1);
	draw_frame(&main);
	while (main.multi.threads_done < NUM_THREADS)
		ft_putstr("");
	edge_detection(&main.sdl.frame_buffer);
	main.ant_al = A_A_DIV;
	draw_frame(&main);
	creat_filters(&main.sdl.frame_buffer);
	draw_to_window(&main.sdl, main.sdl.frame_buffer.data);
	rt_loop_and_exit(&main.sdl);
	SDL_Quit();
	return (0);
}
