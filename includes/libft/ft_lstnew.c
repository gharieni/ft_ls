/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:39:20 by gmelek            #+#    #+#             */
/*   Updated: 2016/11/20 16:50:48 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elem;

	elem = (t_list*)malloc(sizeof(*elem));
	if (elem)
	{
		if (!content)
		{
			elem->content = NULL;
			elem->content_size = 0;
		}
		else
		{
			elem->content = malloc(content_size);
			elem->content = ft_memcpy(elem->content, content, content_size);
			elem->content_size = content_size;
		}
		elem->next = NULL;
	}
	return (elem);
}
