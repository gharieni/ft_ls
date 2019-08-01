/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:47:27 by ghamelek          #+#    #+#             */
/*   Updated: 2018/10/01 19:47:28 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char const *s_end;

	if (s == NULL)
		return (NULL);
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '\0')
		return (ft_strnew(0));
	s_end = s + ft_strlen(s) - 1;
	while (*s_end == ' ' || *s_end == '\t' || *s_end == '\n')
		s_end--;
	return (ft_strsub(s, 0, s_end - s + 1));
}
