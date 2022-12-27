/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml_file_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:28:46 by mmakinen          #+#    #+#             */
/*   Updated: 2022/12/21 15:28:54 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yaxml.h"

size_t	xml_get_size(const char *path)
{
	int		fd;
	size_t	size;
	size_t	temp;
	char	buf[4096];

	size = 0;
	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (xml_return_error("ERROR: Input is directory"));
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (xml_return_error("ERROR: Could not load file"));
	temp = read(fd, buf, 4096);
	while (temp > 0)
	{
		size += temp;
		temp = read(fd, buf, 4096);
	}
	if (close(fd) == -1)
		return (xml_return_error("ERROR: Could not close file"));
	return (size);
}

int	xml_read_file(t_buffers *buf, const char *path)
{
	int	fd;

	buf->buff_len = xml_get_size(path);
	if (buf->buff_len == FALSE)
		return (FALSE);
	buf->mem = (char *)malloc(sizeof(buf->mem) * buf->buff_len + 1);
	if (!buf->mem)
		return (xml_error_free(buf, "Buffer malloc failed"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (xml_error_free(buf, "Could not load file"));
	if (read(fd, buf->mem, buf->buff_len) == -1)
		return (xml_error_free(buf, "Could not read file"));
	buf->mem[buf->buff_len] = '\0';
	if (close(fd) == -1)
		return (xml_error_free(buf, "Could not close file"));
	return (TRUE);
}
