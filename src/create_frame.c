/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:56:49 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/02 17:21:55 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	create_frame(t_main *main)
{
	create_threads(main, 1);
	draw_frame(main);
	sleep(1);
	edge_detection(&main->sdl.frame_buffer);
	main->ant_al = A_A_DIV;
	draw_frame(main);
	if (main->sdl.stereocopy == TRUE)
		create_stereoscope(main, main->scene.cam.transform);
	else
		create_motion_blur(main);
}
