/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/03 13:27:22 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/rt.h"

//Copys 1d arrey to texture and draws it.

void	draw_filter(t_sdl *sdl, int *filter_type)
{
	if (*filter_type == STEREOSCOPY)
	{
		if (sdl->stereocopy == TRUE)
			draw_to_window(sdl, sdl->frame_buffer.stereocopy);
		else if (sdl->event.key.keysym.sym == SDLK_UP)
			*filter_type = NORMAL;
		else
			*filter_type = EDGE;
	}
	else if (*filter_type == NORMAL)
		draw_to_window(sdl, sdl->frame_buffer.data);
	else
	{
		creat_filters(&sdl->frame_buffer, *filter_type);
		draw_to_window(sdl, sdl->frame_buffer.filter);
	}
}

static void	free_all(t_main *main)
{
	SDL_DestroyTexture(main->sdl.texture);
	SDL_DestroyWindow(main->sdl.win);
	SDL_DestroyRenderer(main->sdl.ren);
	free(main->sdl.frame_buffer.data);
	free(main->sdl.frame_buffer.filter);
	free(main->sdl.frame_buffer.mask);
	free(main->sdl.frame_buffer.motion_calc);
	vec_free(&main->scene.objects);
	vec_free(&main->scene.lights);
	free(main->sdl.frame_buffer.stereocopy);
}

// Infinite loop to handle the window.

void	rt_loop_and_exit(t_sdl *sdl, t_main *main)
{
	int	quit;
	int	filter_type;

	quit = 0;
	filter_type = NORMAL;
	while (quit == 0)
	{
		if (SDL_PollEvent(&sdl->event) != 0)
			key_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type);
	}
	free_all(main);
}

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
			main->sdl.frame_buffer.mask[((y * WIN_W) + x)] == 0)
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
	main.settings.edge_detection_presission = 0.02;
	main.settings.orig_ant_al = 6;
	if (ac == 2)
	{
		if (read_file(&main, &doc, av[1]) == 1)
			return (1);
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
	create_frame(&main);
	rt_loop_and_exit(&main.sdl, &main);
	SDL_Quit();
	return (0);
}
