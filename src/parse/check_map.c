/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:57 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 16:16:30 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

static t_checker_map	*gen_checker_board(char *line);
static t_uv_map			*gen_bump_map(char *line, t_vars *vars);
static void				assign_value_by_type(void *content, t_type type, \
							t_uv_map *uvmap, t_checker_map *checker);

void	check_map(t_vars *vars, void *content, char *line, t_type type)
{
	t_uv_map		*uvmap;
	t_checker_map	*checker;

	uvmap = NULL;
	checker = NULL;
	if (*line == '\n' || *line == '\0')
		return ;
	else if (ft_strncmp(line, "xpm ", 4) == 0)
		uvmap = gen_bump_map(line + 3, vars);
	else if (ft_strncmp(line, "chk ", 4) == 0)
		checker = gen_checker_board(line + 3);
	else
		ft_error("File Format Error");
	assign_value_by_type(content, type, uvmap, checker);
}

static t_checker_map	*gen_checker_board(char *line)
{
	t_checker_map	*out;

	out = ft_calloc(1, sizeof(t_checker_map));
	out->rgb1 = parse_vec(&line);
	out->rgb2 = parse_vec(&line);
	out->width = parse_int(&line);
	out->height = parse_int(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	return (out);
}

static t_uv_map	*gen_bump_map(char *line, t_vars *vars)
{
	t_uv_map	*out;

	out = ft_calloc(1, sizeof(t_uv_map));
	out->texture = ft_calloc(1, sizeof(t_uv_data));
	out->texture->path = parse_path(&line);
	out->texture->mlx = vars->mlx_data.mlx;
	out->normal = ft_calloc(1, sizeof(t_uv_data));
	out->normal->path = parse_path(&line);
	out->normal->mlx = vars->mlx_data.mlx;
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	return (out);
}

static void	assign_value_by_type(void *content, t_type type, \
				t_uv_map *uvmap, t_checker_map *checker)
{
	if (type == SPHERE)
	{
		((t_sphere *)content)->uvmap = uvmap;
		((t_sphere *)content)->checker = checker;
	}
	else if (type == PLANE)
	{
		((t_plane *)content)->uvmap = uvmap;
		((t_plane *)content)->checker = checker;
	}
	else if (type == CYLINDER)
	{
		((t_cylinder *)content)->uvmap = uvmap;
		((t_cylinder *)content)->checker = checker;
	}
}
