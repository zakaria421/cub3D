/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:39:10 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/24 17:28:45 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str == NULL && len == 0)
		return ((char *)str);
	if (to_find[i] == '\0')
		return ((char *)(str));
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j] != '\0' && i + j < len)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
	return (0);
}
