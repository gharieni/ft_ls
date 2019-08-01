/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:39:29 by ghamelek          #+#    #+#             */
/*   Updated: 2018/10/01 19:39:31 by ghamelek         ###   ########.fr       */
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
