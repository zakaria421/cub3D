/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:18:17 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/24 17:28:31 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len == 0 || start > ft_strlen(s))
		return (p = malloc(1), p[i] = '\0', p);
	else if (len >= ft_strlen(s))
	{
		p = malloc((ft_strlen(s) - start) + 1);
		if (!p)
			return (NULL);
	}
	else
	{
		p = malloc(len + 1);
		if (!p)
			return (NULL);
	}
	while (i < len && s[start] != '\0')
		p[i++] = s[start++];
	return (p[i] = '\0', p);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			j++;
		while (s[i] && s[i] != c)
		{
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (j);
}

static	int	ft_start(int start, int end, char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			return (i + start + end);
		}
		i++;
	}
	return (0);
}

static void	free_ptr(char **ptr, int r)
{
	while (r >= 0)
	{
		free(ptr[r]);
		r--;
	}
	free (ptr);
	return ;
}

static int	ft_end(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		size;
	int		r;
	int		end;
	int		start;

	r = 0;
	start = 0;
	end = 0;
	if (!s)
		return (0);
	size = ft_count(s, c);
	ptr = malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	while (r < size)
	{
		start = ft_start(start, end, s + start + end, c);
		end = ft_end(s + start, c);
		ptr[r] = ft_substr(s, start, end);
		if (ptr[r] == NULL)
			return (free_ptr(ptr, r), NULL);
		r++;
	}
	return (ptr[r] = NULL, ptr);
}
