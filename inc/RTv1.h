/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:16:55 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:53:00 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "objects.h"
# include "SDL2/SDL.h"

# define WIN_W 1615
# define WIN_H 1009
# define GAMMA 2.2
# define AMBIENT 0.0001
# define LIGHTBULB_SIZE 0.0001
# define TRUE 1
# define FALSE 0

typedef struct s_hit_record
{
	t_point	loc;
	t_vec3	normal;
	int		is_hit;
	double	max_distance;
	double	closest_distance;
	int		closest_id;
	t_color	color;
	double	light_level;
}	t_hit_record;

typedef struct s_frame_buffer
{
	char			*data;
	size_t			bits_per_pixel;
	unsigned long	line_length;
	int				height;
	int				texture_pitch;
	int				*texture_data;
}	t_frame_buffer;

typedef struct s_context
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
	t_cam			cam;
	t_light			light;
	t_ray			ray;
	t_light			ambient;
	t_ray			normal;
	t_hit_record	hit;
	t_vec			scene;
	int				parse_state;
	t_object		obj;
	char			**words;
	char			**temp;
	char			*line;
	char			*trimmed;
	int				render;
	int				quit;
	int				gnl;
	SDL_Event		e;
}	t_context;

int				init(t_context *ctx);
void			draw(t_context *ctx);
void			write_buffer(t_context *ctx,
					int *texture_data,
					int *texture_pitch);
double			get_light_level(t_ray normal,
					t_ray ray,
					t_context *ctx,
					int id);
t_color			shade(t_object obj,
					double shading);
void			init_camera(t_cam *cam,
					t_point loc);
void			img_pixel_put(t_frame_buffer *fb,
					unsigned int x,
					unsigned int y,
					t_color color);
t_hit_record	hit_record_new(void);
void			intersects(t_context *ctx, double distance);
int				intersects_sphere(t_ray *ray,
					t_object *sphere,
					double *distance);
int				intersects_plane(t_ray *ray,
					t_object *plane,
					double *distance);
int				intersects_cylinder(t_ray *ray,
					t_object *cylinder,
					double *distance);
int				intersects_cone(t_ray *ray,
					t_object *cone,
					double *distance);
t_vec3			get_sphere_normal(t_context *ctx);
t_vec3			get_plane_normal(t_context *ctx);
t_vec3			get_cylinder_normal(t_context *ctx);
t_vec3			get_cone_normal(t_context *ctx);
int				handle_args(int argc,
					char **argv,
					t_context *ctx);
void			handle_events(t_context *ctx);
void			check_type(char **str,
					t_context *ctx);
t_point			read_triple(char **strs);
int				ft_atof(char *str,
					double *result);
void			init_camera(t_cam *cam, t_point loc);
void			calc_current_ray(t_context *ctx,
					unsigned int x,
					unsigned int y);
void			set_camera(t_context *ctx);
t_vec3			vec3_rotate(t_vec3 u, t_vec3 v);
double			to_radians(double degrees);
void			rt_close(t_context *ctx);
int				test_sphere(t_ray normal,
					t_vec3 to_light,
					t_object *obj,
					double *distance);
int				test_plane(t_ray normal,
					t_vec3 to_light,
					t_object *obj,
					double *distance);
int				test_cone(t_ray normal,
					t_vec3 to_light,
					t_object *obj,
					double *distance);
int				test_cylinder(t_ray normal,
					t_vec3 to_light,
					t_object *obj,
					double *distance);
void			move_cam(t_context *ctx,
					t_vec3 dir);

#endif
