/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:13:27 by seunan            #+#    #+#             */
/*   Updated: 2023/12/14 14:55:30 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parse.h"

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*buf;
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	size = read(fd, buf, BUFFER_SIZE);
	return (repeat_read(backup, fd, buf, size));
}

char	*repeat_read(char **backup, int fd, char *buf, int size)
{
	char	*tmp;

	while (size > 0)
	{
		buf[size] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		tmp = ft_strjoin(backup[fd], buf);
		free(backup[fd]);
		backup[fd] = tmp;
		if (ft_strchr(backup[fd], '\n'))
			break ;
		size = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (size < 0)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	return (ret_line(&backup[fd]));
}

char	*ret_line(char **backup)
{
	char	*line;
	char	*cut;

	line = NULL;
	if (*backup)
	{
		cut = ft_strchr(*backup, '\n');
		if (cut)
			return (update_line(backup, line, cut));
		if (**backup == '\0')
		{
			free(*backup);
			*backup = NULL;
		}
		line = *backup;
		*backup = NULL;
	}
	return (line);
}

char	*update_line(char **backup, char *line, char *cut)
{
	char	*tmp;

	tmp = ft_strdup(cut + 1);
	*(cut + 1) = '\0';
	line = ft_strdup(*backup);
	free(*backup);
	*backup = tmp;
	return (line);
}
