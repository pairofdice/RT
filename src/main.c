/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/23 13:45:27 by jjuntune         ###   ########.fr       */
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
		else if (sdl->event.key.keysym.sym == SDLK_DOWN)
			*filter_type = EDGE;
		else
			*filter_type = NORMAL;
	}
	else if (*filter_type == NORMAL)
		draw_to_window(sdl, sdl->frame_buffer.data);
	else
	{
		creat_filters(&sdl->frame_buffer, *filter_type);
		draw_to_window(sdl, sdl->frame_buffer.filter);
	}
}

static void	free_obj_textures(t_vec	*obj_in)
{
	t_object	*obj;
	size_t		i;

	i = 0;
	while (i < obj_in->len)
	{
		obj = (t_object *) vec_get(obj_in, i);
		if (obj->texture.loaded == TRUE)
			SDL_FreeSurface(obj->texture.surface);
		i++;
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
	free_obj_textures(&main->scene.objects);
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
	filter_type = STEREOSCOPY;
	while (quit == 0)
	{
		if (SDL_PollEvent(&sdl->event) != 0)
			key_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type);
	}
	free_all(main);
}

int	main(int ac, char **av)
{
	t_main		main;

	if (ac == 2)
	{
		if (!read_file(&main, av[1]))
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
