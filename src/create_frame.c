/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:56:49 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/19 17:28:17 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	create_frame(t_main *main)
{
	create_threads(main, 1);
	set_blocked_lights(main);
	draw_frame(main);
	sleep(1);
	edge_detection(&main->sdl.frame_buffer, main->settings);
	main->settings.ant_al = main->settings.orig_ant_al;
	draw_frame(main);
	if (main->sdl.stereocopy == TRUE)
		create_stereoscope(main, main->scene.cam.transform);
	else
		create_motion_blur(main);
}
