/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:37:00 by seunan            #+#    #+#             */
/*   Updated: 2023/12/19 22:34:38 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"

static void	check_identifier(t_vars *vars, char *line);
static int	protected_open(char *path);

/* gnl로 한줄씩 받아서 알맞는 구조체에 넣는 함수 */
void	parse_rt(t_vars *vars, char *path)
{
	char	*line;
	int		fd;

	fd = protected_open(path);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		check_identifier(vars, line);
		free(line);
	}
	if (vars->camera.cnt == 0 || vars->ambient.cnt == 0 || vars->light == NULL)
		ft_error("File Format Error");
}

static void	check_identifier(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\n' && *(line + 1) == '\0')
		return ;
	else if (ft_strncmp(line, "A ", 2) == 0)
		gen_ambient(&(vars->ambient), line + 1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		gen_camera(&(vars->camera), line + 1);
	else if (ft_strncmp(line, "L ", 2) == 0)
		gen_light(&(vars->light), line + 1);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		gen_sphere(vars, line + 2);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		gen_plane(vars, line + 2);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		gen_cylinder(vars, line + 2);
	else if (ft_strncmp(line, "cn ", 3) == 0)
		gen_cone(vars, line + 2);
	else
		ft_error("File Format Error");
}

static int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}
