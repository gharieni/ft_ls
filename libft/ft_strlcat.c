/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 18:12:14 by gmelek            #+#    #+#             */
/*   Updated: 2016/11/20 14:14:31 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	res;
	unsigned int	j;

	j = 0;
	i = ft_strlen(dst);
	res = ft_strlen(src) + i;
	if (size <= i || !size || !dst || !src)
		return (size + (res - i));
	while (i < size)
		dst[i++] = src[j++];
	dst[--i] = '\0';
	return (res);
}
