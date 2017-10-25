/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:28:36 by gmelek            #+#    #+#             */
/*   Updated: 2016/11/20 15:30:23 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new_str;

	new_str = (char*)malloc(sizeof(*new_str) * (ft_strlen(s1) + 1));
	if (new_str == NULL)
		return (NULL);
	return (ft_strcpy(new_str, s1));
}
