/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:13:27 by seunan            #+#    #+#             */
/*   Updated: 2023/12/14 14:56:01 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*answer;
	size_t	i;

	answer = malloc((ft_strlen(s) + 1));
	if (!answer)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		answer[i] = s[i];
		++i;
	}
	answer[i] = '\0';
	return (answer);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0')
	{
		s[i] = s2[j];
		++i;
		++j;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	return (NULL);
}
