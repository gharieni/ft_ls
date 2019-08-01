/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:43:43 by ghamelek          #+#    #+#             */
/*   Updated: 2018/10/01 22:02:40 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;
	int		len;

	len = ft_strlen(src);
	str = ft_strnew(len);
	i = 0;
	while (str && i < len)
	{
		str[i] = src[i];
		i++;
	}
	if (str)
		str[i] = '\0';
	return (str);
}
