/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:46 by seunan            #+#    #+#             */
/*   Updated: 2023/12/11 15:52:13 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;

	mem = malloc(size * count);
	if (!mem)
		ft_error("Failed to allocate memory.");
	ft_bzero(mem, size * count);
	return ((void *) mem);
}
