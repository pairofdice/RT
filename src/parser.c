/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:10:05 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/02 16:17:55 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"

int	read_file(t_main *main, char *file)
{
	t_xml_doc	doc;

	doc.version = NULL;
	doc.encoding = NULL;
	main->sdl.stereocopy = FALSE;
	scene_new(&main->scene);
	load_perlin_data(&main->scene.perlin);
	if (!xml_doc_load(&doc, file))
	{
		ft_putendl_fd("ERROR: Couldn't read file!", 2);
		return (FALSE);
	}
	if (!read_xml(&doc, main))
		return (FALSE);
	xml_doc_free(&doc);
	return (TRUE);
}
