
#include "libft.h"
#include "parse.h"

t_checker_map	*gen_checker_board(char *line)
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

t_uv_map	*gen_bump_map(char *line)
{
	t_uv_map	*out;

	out = ft_calloc(1, sizeof(t_uv_map));
	out->texture = ft_calloc(1, sizeof(t_uv_data));
	out->texture->path = parse_path(&line);
	out->normal = ft_calloc(1, sizeof(t_uv_data));
	out->normal->path = parse_path(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	return (out);
}

void	check_map(void *content, char *line, t_type type)
{
	t_uv_map		*uvmap;
	t_checker_map	*checker;

	uvmap = NULL;
	checker = NULL;
	if (*line == '\n' || *line == '\0')
		return ;
	else if (ft_strncmp(line, "xpm ", 4) == 0)
		uvmap = gen_bump_map(line + 3);
	else if (ft_strncmp(line, "chk ", 4) == 0)
		checker = gen_checker_board(line + 3);
	else
		ft_error("File Format Error");
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
