/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:46:38 by ghamelek          #+#    #+#             */
/*   Updated: 2018/10/01 19:46:39 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	cur;

	cur = 0;
	while (s2[cur] != '\0' && cur < n)
	{
		s1[cur] = s2[cur];
		cur++;
	}
	while (cur < n)
	{
		s1[cur] = '\0';
		cur++;
	}
	return (s1);
}
