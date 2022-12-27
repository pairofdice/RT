/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/19 13:50:35 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/rt.h"

//Copys 1d arrey to texture and draws it.

void	draw_filter(t_sdl *sdl, int *filter_type, int i)
{
	if (i == 1)
	{
		if (sdl->event.key.keysym.sym == SDLK_DOWN && *filter_type > 0)
			*filter_type -= 1;
		else if (sdl->event.key.keysym.sym == SDLK_DOWN)
			*filter_type = EDGE;
		else if (sdl->event.key.keysym.sym == SDLK_UP && *filter_type < 6)
			*filter_type += 1;
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = STEREOSCOPY;
	}
	if (*filter_type == STEREOSCOPY)
	{
		if (sdl->stereocopy == TRUE)
			draw_to_window(sdl, sdl->frame_buffer.stereocopy);
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = NORMAL;
		else
			*filter_type = EDGE;
	}
	if (*filter_type == NORMAL)
		draw_to_window(sdl, sdl->frame_buffer.data);
	else
	{
		creat_filters(&sdl->frame_buffer, *filter_type);
		draw_to_window(sdl, sdl->frame_buffer.filter);
	}
}

static void	free_buffers_and_sdl(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyWindow(sdl->win);
	SDL_DestroyRenderer(sdl->ren);
	free(sdl->frame_buffer.data);
	free(sdl->frame_buffer.filter);
	free(sdl->frame_buffer.mask);
	free(sdl->frame_buffer.motion_calc);
}

// Infinite loop to handle the window.

void	rt_loop_and_exit(t_sdl *sdl)
{
	int	quit;
	int	filter_type;

	quit = 0;
	filter_type = NORMAL;
	while (quit == 0)
	{
		if (SDL_PollEvent(&sdl->event) != 0)
			key_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type, 0);
	}
	free_buffers_and_sdl(sdl);
}

void	tests(t_main *main, int draw_debug); // unit tests
int	anti_aliasing(t_main *main, int pixel_x, int pixel_y, int ant_a);


void	render_image_debug(t_main *main, int task, int ant_al)
{
	t_main	copy;
	int		y;
	int		x;
	int		color;

	y = task;
	copy = (t_main) * main;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			copy.ray.hit.color = color_new(0, 0, 0);
			while (ant_al != 1 && x < WIN_W && \
			main->sdl.frame_buffer.mask[((y	* WIN_W) + x)] == 0)
				x++;
			if (x == WIN_W)
				break ;
			color = anti_aliasing(&copy, x, y, ant_al);
			main->sdl.frame_buffer.data[((y * WIN_W) + x++)] = color;
		}
		y += NUM_TASKS;
	}
}

int	main(int ac, char **av)
{
	t_main		main;
	t_xml_doc	doc;
	
	main.sdl.stereocopy = FALSE;
	main.ant_al = 0;
	if (ac == 2)
	{
		if (!xml_doc_load(&doc, av[1]))
		{
			ft_putendl_fd("ERROR: Couldn't read file!", 2);
			return (1);
		}
		read_xml(&doc, &main);
		xml_doc_free(&doc);
	}
	else
	{
			ft_putendl_fd("Usage: <input>.xml", 2);
			return (1);
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (initialize_window(&main) == 0)
		return (1);
		//FREE BUFFERS!!!!!!
	int draw_debug = 2;


	if (draw_debug == 1)
	{
		create_threads(&main, 1);
		draw_frame(&main);
		edge_detection(&main.sdl.frame_buffer);
		main.ant_al = A_A_DIV;
		draw_frame(&main);
		if (main.sdl.stereocopy == TRUE)
			create_stereoscope(&main, main.scene.cam.transform);
		else
			create_motion_blur(&main);
	}
	if (draw_debug == 2)
	{
		render_image_debug(&main, 0, 1);
	}
/* 	tests(&main, draw_debug); */
	rt_loop_and_exit(&main.sdl);
	vec_free(&main.scene.objects);
	vec_free(&main.scene.lights);
	free(main.sdl.frame_buffer.stereocopy);
	SDL_Quit();
	return (0);
}