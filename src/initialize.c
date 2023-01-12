/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:10 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/11 17:59:53 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static int	initialize_buffers(t_frame_buffer *fb)
{
	fb->data_len = (WIN_H * WIN_W);
	fb->data = (int *)malloc(sizeof(int) * fb->data_len);
	fb->stereocopy = (int *)malloc(sizeof(int) * fb->data_len);
	fb->filter = (int *)malloc(sizeof(int) * fb->data_len);
	fb->mask = (char *)malloc(sizeof(char) * fb->data_len);
	fb->motion_calc = (t_color *)malloc(sizeof(t_color) * fb->data_len);
	if (fb->data == NULL || fb->filter == NULL
		|| fb->motion_calc == NULL || fb->stereocopy == NULL)
		return (0);
	return (1);
}

int	initialize_window(t_main *main)
{
	main->sdl.win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (main->sdl.win == NULL)
		return (0);
	main->sdl.ren = SDL_CreateRenderer(main->sdl.win, -1, 0);
	if (main->sdl.ren == NULL)
		return (0);
	main->sdl.texture = SDL_CreateTexture(main->sdl.ren,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (main->sdl.texture == NULL)
		return (0);
	if (initialize_buffers(&main->sdl.frame_buffer) == 0)
		return (0);
	init_pthread(main);
	return (1);
}

void	initialize_camera(t_cam *cam, t_matrix transform)
{
	cam->pos = point_new(0.0, 0.0, 0.0);
	cam->coi = point_new(0.0, 0.0, 0.0);
	cam->v_up = vector_new(0.0, 1.0, 0.0);
	cam->n = vector_new(0.0, 0.0, 1.0);
	cam->u = vector_new(-1.0, 0.0, 0.0);
	cam->v = vector_new(0.0, 1.0, 0.0);
	cam->c = tuple_sub(point_new(0, 0, 0), tuple_scalar_mult(cam->n, 0.1));
	cam->plane_h = tan(1.04719 / 2) * 2 * 0.1;
	cam->plane_w = cam->plane_h * ((float)WIN_W / WIN_H);
	cam->l = tuple_sub(cam->c,
			tuple_scalar_mult(cam->u, (cam->plane_w / 2.0)));
	cam->l = tuple_sub(cam->l,
			tuple_scalar_mult(cam->v, cam->plane_h / 2.0));
	cam->transform = coi_transform(cam, transform);
}

void	initialize_ray(t_ray *ray, double x, double y, t_cam *cam)
{
	ray->orig = point_new(0, 0, 0);
	ray->dir = tuple_add(cam->l, tuple_scalar_mult(cam->u,
				x * (cam->plane_w / WIN_W)));
	ray->dir = tuple_add(ray->dir, tuple_scalar_mult(cam->v,
				y * (cam->plane_h / WIN_H)));
	ray->dir = tuple_sub(cam->pos, ray->dir);
	ray->dir = tuple_unit(ray->dir);
	*ray = ray_transform(ray, &cam->transform);
	vec_new(&ray->xs.vec, 4, sizeof(t_intersection));
	ray->remaining = 5;
}
