/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:46:00 by ghamelek          #+#    #+#             */
/*   Updated: 2018/10/01 19:46:01 by ghamelek         ###   ########.fr       */
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
