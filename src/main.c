/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/19 13:48:20 by jjuntune         ###   ########.fr       */
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
			kay_hooks(sdl, &quit, &filter_type);
		draw_filter(sdl, &filter_type, 0);
	}
	free_buffers_and_sdl(sdl);
}

void	tests(t_main *main, int draw_debug); // unit tests

int	main(void)
{
	t_main		main;
	t_matrix	rotate;
	t_matrix	cam_scale;
	t_matrix	scale;
	double	x_r;
	double	y_r;
	double	z_r;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (initialize_window(&main) == 0)
		return (1);
		//FREE BUFFERS!!!!!!
	
	main.sdl.stereocopy = FALSE;
	scene_new(&main.scene);
	
	main.cam.transform = matrix_translate(10, 0.0, -10.0);
	main.cam.coi_transform = matrix_translate(0, 0.0, 15.0);

	cam_scale = matrix_scale(1,1,1);
	main.cam.transform = matrix_multiply(&main.cam.transform, &cam_scale);
	main.cam.motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1,0,0)));
	main.cam.coi_motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1,0,0)));

	main.light = point_light_new(point_new(0, 0, 0.0), color_new(1,1,1));
	vec_push(&main.scene.lights, &main.light);
	// main.light = point_light_new(point_new(20, 20, 0.0), color_new(1,0,0));
	// vec_push(&main.scene.lights, &main.light);
	// main.light = point_light_new(point_new(-20, -20, 0.0), color_new(0,1,0));
	// vec_push(&main.scene.lights, &main.light);
	// main.light = point_light_new(point_new(-20, 20, 10.0), color_new(0,0,1));
	// vec_push(&main.scene.lights, &main.light);


	
	// main.light.pos = point_new(10, 0, 0);
	// t_object o;
	
	// o = object_new(SPHERE);
	// o.id = 0;
	// vec_push(&main.scene.objects, &o);
	// o = object_new(SPHERE);
	// o.id = 1;
	// vec_push(&main.scene.objects, &o);
	// o = object_new(SPHERE);
	// o.id = 2;
	// vec_push(&main.scene.objects, &o);
	// o = object_new(SPHERE);
	// o.id = 3;
	// vec_push(&main.scene.objects, &o);
	// o = object_new(SPHERE);
	// o.id = 4;
	// vec_push(&main.scene.objects, &o);
	// o = object_new(SPHERE);
	// o.id = 5;
	// vec_push(&main.scene.objects, &o);
	// o = object_new(SPHERE);
	// o.id = 6;
	// vec_push(&main.scene.objects, &o);
	
	
	main.obj[0] = object_new(SPHERE);
	main.obj[0].transform = matrix_translate(0.0, 0.0, 15.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;
	rotate = matrix_rotate_x(x_r);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &rotate);
	scale = matrix_scale(5,5,5);
	main.obj[0].transform = matrix_multiply(&main.obj[0].transform, &scale);
	main.obj[0].material.color = color_new(1,1,1);
	main.obj[0].motion = motion_new(FALSE, 5.0, tuple_unit(vector_new(1,0,0)));
	main.obj[0].material.pattern.pattern_id = NONE;
	main.obj[0].material.pattern.pattern_perlin = TRUE;
	main.obj[0].negative = FALSE;
	main.obj[0].id = 0;
	
	main.obj[1] = object_new(SPHERE);
	main.obj[1].transform = matrix_translate(2.0, 2.0, 15.0);
											x_r = M_PI_2;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &rotate);
	scale = matrix_scale(4,4,4);
	main.obj[1].transform = matrix_multiply(&main.obj[1].transform, &scale);
	main.obj[1].material.color = color_new(1.0, 1.0, 1.0);
	main.obj[1].material.pattern.pattern_id = NONE;
	main.obj[1].material.pattern.pattern_perlin = TRUE;
	main.obj[1].negative = TRUE;
	main.obj[1].id = 1;

	main.obj[2] = object_new(SPHERE);
	main.obj[2].transform = matrix_translate(2.0, -2.0, 15.0);
											x_r = -M_PI_2;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &rotate);
	scale = matrix_scale(4,4,4);
	main.obj[2].transform = matrix_multiply(&main.obj[2].transform, &scale);
	main.obj[2].material.color = color_new(1.0, 0.5, 1.0);
	main.obj[2].material.pattern.pattern_id = NONE;
	main.obj[2].material.pattern.pattern_perlin = TRUE;
	main.obj[2].negative = TRUE;
	main.obj[2].id = 2;


	main.obj[3] = object_new(SPHERE);
	main.obj[3].transform = matrix_translate(-2.0, 2.0, 15.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &rotate);
	scale = matrix_scale(4,4,4);
	main.obj[3].transform = matrix_multiply(&main.obj[3].transform, &scale);
	main.obj[3].material.color = color_new(1, 0.5,0);
	main.obj[3].material.pattern.pattern_id = NONE;
	main.obj[3].material.pattern.pattern_perlin = FALSE;
	main.obj[3].negative = TRUE;
	main.obj[3].id = 3;

	main.obj[4] = object_new(SPHERE);
	main.obj[4].transform = matrix_translate(-2.0, -2.0, 15.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &rotate);
	scale = matrix_scale(4,4,4);
	main.obj[4].transform = matrix_multiply(&main.obj[4].transform, &scale);
	main.obj[4].material.color = color_new(1, 0.5,0);
	main.obj[4].material.pattern.pattern_id = NONE;
	main.obj[4].material.pattern.pattern_perlin = FALSE;
	main.obj[4].negative = TRUE;
	main.obj[4].id = 4;
	
	main.obj[5] = object_new(SPHERE);
	main.obj[5].transform = matrix_translate(0.0, 0.0, 10.0);
											x_r = 0.0;
											y_r = 0.0;
											z_r = 0.0;

	rotate = matrix_rotate_x(x_r);
	main.obj[5].transform = matrix_multiply(&main.obj[5].transform, &rotate);
	rotate = matrix_rotate_y(y_r);
	main.obj[5].transform = matrix_multiply(&main.obj[5].transform, &rotate);
	rotate = matrix_rotate_z(z_r);
	main.obj[5].transform = matrix_multiply(&main.obj[5].transform, &rotate);
	scale = matrix_scale(5,5,5);
	main.obj[5].transform = matrix_multiply(&main.obj[5].transform, &scale);
	main.obj[5].material.color = color_new(1, 1, 1);
	main.obj[5].material.pattern.pattern_id = GRID;
	main.obj[5].material.pattern.pattern_perlin = TRUE;
	main.obj[5].negative = TRUE;
	main.obj[5].id = 5;
	
	vec_push(&main.scene.objects, &main.obj[0]);
	vec_push(&main.scene.objects, &main.obj[1]);
	vec_push(&main.scene.objects, &main.obj[2]);
	vec_push(&main.scene.objects, &main.obj[3]);
	vec_push(&main.scene.objects, &main.obj[4]);
	vec_push(&main.scene.objects, &main.obj[5]);
	
	int draw_debug = 0;

	if (!draw_debug)
	{
		initialize_camera(&main.cam, main.cam.transform);
		load_perlin_data(&main.perlin);
		create_threads(&main, 1);
		draw_frame(&main);
		edge_detection(&main.sdl.frame_buffer);
		main.ant_al = A_A_DIV;
		draw_frame(&main);
		// if (main.sdl.stereocopy == TRUE)
		// 	create_stereoscope(&main, cam_scale, main.cam.transform);
		/* create_motion_blur(&main); */
	}
/* 	tests(&main, draw_debug); */
	rt_loop_and_exit(&main.sdl);
	SDL_Quit();
	return (0);
}