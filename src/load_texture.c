/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:00:47 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/18 18:32:13 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	image_load(const char *file, t_image *image)
{
	image->loaded = FALSE;
	image->surface = SDL_LoadBMP(file);
	if (!image->surface)
		return (-1);
	image->w = image->surface->w;
	image->h = image->surface->h;
	image->pitch = image->surface->pitch;
	image->bpp = image->surface->format->BytesPerPixel;
	if (image->bpp != 4)
	{
		image->incorrect_bpp = TRUE;
		return (-1);
	}
	image->linesize = (image->pitch / image->bpp);
	image->size = image->h * image->linesize;
	SDL_LockSurface(image->surface);
	image->pixels = NULL;
	image->pixels = (uint32_t *)(image->surface->pixels);
	SDL_UnlockSurface(image->surface);
	image->loaded = TRUE;
	return (1);
}