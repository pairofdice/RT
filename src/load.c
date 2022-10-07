/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/04 15:41:21 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	sf_free_array(void **array)
{
	void	**temp;

	temp = *array;
	while (*temp)
	{
		ft_memdel(temp);
		temp++;
	}
	free(*array);
	*array = NULL;
}

static void	sf_process_line(t_context *ctx, char **words)
{
	ctx->trimmed = ft_strtrim(*words);
	if (!ctx->trimmed)
		rt_close(ctx);
	if (ft_strncmp(ctx->trimmed, "loc", 3) == 0)
		ctx->obj.loc = read_triple(words);
	if (ft_strncmp(ctx->trimmed, "translate", 9) == 0)
		ctx->obj.loc = vec3_add(ctx->obj.loc, read_triple(words));
	if (ft_strncmp(ctx->trimmed, "dir", 3) == 0)
		ctx->obj.rot = vec3_unit(read_triple(words));
	if (ft_strncmp(ctx->trimmed, "rotate", 6) == 0)
		ctx->obj.rot = vec3_unit(vec3_rotate(ctx->obj.rot,
					read_triple(words)));
	if (ft_strncmp(ctx->trimmed, "coi", 3) == 0)
		ctx->obj.coi = read_triple(words);
	if (ft_strncmp(ctx->trimmed, "up", 2) == 0)
		ctx->cam.scene_up = read_triple(words);
	if (ft_strncmp(ctx->trimmed, "color", 5) == 0)
		ctx->obj.color = read_triple(words);
	if (ft_strncmp(ctx->trimmed, "size", 4) == 0)
	{
		(words)++;
		ft_atof(*words, &ctx->obj.size);
	}
	ft_strdel(&ctx->trimmed);
}

static void	sf_parse_line(t_context *ctx)
{
	if (ctx->parse_state == NOTHING && **ctx->words == '{')
		check_type(ctx->words, ctx);
	else if (**ctx->words == '}')
	{
		if (ctx->obj.type == CAMERA)
			set_camera(ctx);
		if (ctx->obj.type == LIGHT)
			ctx->light.loc = ctx->obj.loc;
		ctx->parse_state = NOTHING;
		if (vec_push(&ctx->scene, &ctx->obj) == -1)
			exit (1);
	}
	else if (ctx->parse_state == PROCESSING)
	{
		if (ctx->words && *ctx->words && **ctx->words)
			sf_process_line(ctx, ctx->words);
	}
}

static int	sf_load_scene(int fd, t_context *ctx)
{
	if (!(vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_object))))
		rt_close(ctx);
	ctx->gnl = 1;
	while (ctx->gnl == 1)
	{
		ctx->gnl = get_next_line(fd, &ctx->line);
		if (ctx->gnl <= 0)
			break ;
		ctx->words = ft_strsplit(ctx->line, ' ');
		if (!ctx->words)
			rt_close(ctx);
		ctx->temp = ctx->words;
		if (*ctx->temp)
			sf_parse_line(ctx);
		sf_free_array((void *)&ctx->temp);
		ft_strdel(&ctx->line);
	}
	if (ctx->gnl != 0)
		return (0);
	return (1);
}

int	handle_args(int argc, char **argv, t_context *ctx)
{
	int	fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			rt_close(ctx);
	}
	else
	{
		ft_putstr("Usage: ./RTv1 <scene>\n");
		exit(1);
	}
	sf_load_scene(fd, ctx);
	close(fd);
	return (1);
}
