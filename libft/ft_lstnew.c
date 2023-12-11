/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:44:41 by seunan            #+#    #+#             */
/*   Updated: 2023/12/11 16:31:41 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, enum e_type type)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	new->content = content;
	new->type = type;
	new->next = 0;
	return (new);
}
