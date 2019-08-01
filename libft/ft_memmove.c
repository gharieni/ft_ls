/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:42:13 by ghamelek          #+#    #+#             */
/*   Updated: 2018/10/01 19:42:14 by ghamelek         ###   ########.fr       */
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
