/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 14:27:54 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"

enum
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	NOT_LIGHT,
	LIGHT,
	CAMERA,
	NOTHING,
	PROCESSING,
};

typedef struct s_object
{
	t_point	loc;
	t_point	coi;
	t_vec3	up;
	t_vec3	rot;
	double	size;
	t_color	color;
	double	brightness;
	int		type;
}	t_object;

typedef struct s_light
{
	t_point	loc;
	t_color	color;
	double	intensity;
}	t_light;

typedef struct s_cam
{
	t_point	virtual_screen_anchor;
	t_point	loc;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	t_vec3	n;
	t_point	coi;
	t_vec3	scene_up;
	double	distance_to_proj;
	t_vec3	cam_to_proj;
	t_vec3	projection_plane_center;
	double	projection_plane_h;
	double	projection_plane_w;
	double	aspect;
}	t_cam;

#endif
