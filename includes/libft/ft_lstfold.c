/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:27:46 by gmelek            #+#    #+#             */
/*   Updated: 2016/11/22 17:28:36 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstfold(t_list *lst, void *(*f)(const void *, const void*, size_t))
{
	void	*result;

	if (lst != NULL)
	{
		result = lst->content;
		lst = lst->next;
		while (lst != NULL)
		{
			result = (*f)(result, lst->content, lst->content_size);
			lst = lst->next;
		}
		return (result);
	}
	return (NULL);
}
