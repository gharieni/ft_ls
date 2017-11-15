/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:28:36 by gmelek            #+#    #+#             */
/*   Updated: 2017/11/15 15:36:29 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



#include <stdlib.h>

char	*ft_strdup	(const char *src)
{
	int		i;
	char	*str;
	int		len;

	len = ft_strlen(src);
	str = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
