/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:25:23 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 16:54:34 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>

typedef struct s_list	t_list;

enum	e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT_POINT
};

struct s_list
{
	void			*content;
	enum e_type		type;
	struct s_list	*next;
	t_color3		albedo;
};

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_error(char *msg);
int		ft_isdigit(int c);
int		ft_issign(char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content, enum e_type type);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(const char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	ft_strtod(char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
