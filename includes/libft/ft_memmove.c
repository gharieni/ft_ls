/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:55:40 by gmelek            #+#    #+#             */
/*   Updated: 2016/11/20 15:25:48 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy2(void *s1, const void *s2, size_t n)
{
	char	*c1;
	char	*c2;

	if (n == 0 || s1 == s2)
		return (s1);
	c1 = (char *)s1;
	c2 = (char *)s2;
	while (n--)
	{
		c1[n] = c2[n];
	}
	return (s1);
}

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	if (s1 < s2)
		return (ft_memcpy(s1, s2, n));
	if (s1 > s2)
		return (ft_memcpy2(s1, s2, n));
	return (s1);
}
