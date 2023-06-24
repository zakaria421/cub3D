/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:40:26 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/24 12:40:33 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//parsing cub3d file
#include "cub3d.h"

char	*ft_strjoin1(char *s1, char const *s2)
{
	char	*p;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = malloc(s2_len + s1_len + 1);
	if (!p)
		return (NULL);
	while (i < s1_len)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		p[i++] = s2[j++];
	return (p[i] = '\0', free(s1), p);
}

void	check_format(char *str)
{
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
	{
		printf("Error: invalid file extension\n");
		exit(1);
	}
}
void	init_map(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->line = NULL;
	map->allin = NULL;
	map->fd = 0;
	map->count = 0;
	map->f = 0;
	map->c = 0;
	map->check.north = 0;
	map->check.south = 0;
	map->check.east = 0;
	map->check.west = 0;
	map->check.floor = 0;
	map->check.ceiling = 0;
	map->check.player = 0;
}
char	*ft_strdupspace(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = 0;
	while (*s1 == ' ' || *s1 == '\t')
		s1++;
	len = ft_strlen(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\n' )
	{	
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
void	check_char(char c)
{
	if ((c > 32 && c < 48) || (c > 57 && c < 127))
	{
		printf("Error: invalid color\n");
		exit(1);
	}
}

int	floorandceiling(char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	color;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	color = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == 'F' || str[i] == 'C')
		i++;
	check_char(str[i]);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	//check_char(str[i]);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	check_char(str[i]);
	while (str[i] >= '0' && str[i] <= '9')
	{
		g = g * 10 + str[i] - '0';
		i++;
	}
	//check_char(str[i]);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	check_char(str[i]);
	while (str[i] >= '0' && str[i] <= '9')
	{
		b = b * 10 + str[i] - '0';
		i++;
	}
	check_char(str[i]);
	if (r > 255 || g > 255 || b > 255)
	{
		printf("Error: invalid color\n");
		exit(1);
	}
	//printf("r = %d, g = %d, b = %d\n", r, g, b);
	color = rgb_to_int(r, g, b);
	return (color);
}

int	direction_take(t_map *map)
{
	int	i;

	i = 0;
	while (map->line[i] == ' ' || map->line[i] == '\t' || map->line[i] == '\n')
		i++;
	if (ft_strncmp(&map->line[i], "NO ", 3) == 0)
	{
		map->no = ft_strdupspace(&map->line[i] + 3);
		map->check.north++;
		map->count++;
	}
	else if (ft_strncmp(&map->line[i], "SO ", 3) == 0)
	{
		map->so = ft_strdupspace(&map->line[i] + 3);
		map->check.south++;
		map->count++;
	}
	else if (ft_strncmp(&map->line[i], "WE ", 3) == 0)
	{
		map->we = ft_strdupspace(&map->line[i] + 3);
		map->check.west++;
		map->count++;
	}
	else if (ft_strncmp(&map->line[i], "EA ", 3) == 0)
	{
		map->ea = ft_strdupspace(&map->line[i] + 3);
		map->check.east++;
		map->count++;
	}
	else if (ft_strncmp(&map->line[i], "F ", 2) == 0)
	{
		map->f = floorandceiling(&map->line[i]);
		map->check.floor++;
		map->count++;
	}
	else if (ft_strncmp(&map->line[i], "C ", 2) == 0)
	{
		map->c = floorandceiling(&map->line[i]);
		map->check.ceiling++;
		map->count++;
	}
	else if (ft_strncmp(&map->line[i], "1", 1) == 0 && map->count == 6)
	{
		return (1);
	}
	else if (map->line[i] == '\0')
	{
		return (0);
	}
	else
	{
		printf("Error: invalid map\n");
		exit(1);
	}
	if (map->check.north > 1 || map->check.south > 1 || map->check.west > 1
		|| map->check.east > 1 || map->check.floor > 1 || map->check.ceiling > 1
		|| map->count > 6)
	{
		printf("Error: invalid map\n");
		exit(1);
	}
	return (0);
}

void	check_the_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->allin[i])
	{
		if (map->allin[i] == 'N' || map->allin[i] == 'S' || map->allin[i] == 'W'
			|| map->allin[i] == 'E')
		{
			map->check.player++;
		}
		if (map->allin[i] != '1' && map->allin[i] != '0'
			&& map->allin[i] != '\n' &&
			map->allin[i] != ' ' && map->allin[i] != '\t'
				&& map->allin[i] != 'N' &&
			map->allin[i] != 'S' && map->allin[i] != 'W'
				&& map->allin[i] != 'E')
		{
			printf("Error: invalid char\n");
			exit(1);
		}
		if (map->allin[i] == '\n')
		{
			j = i;
			j++;
			while (map->allin[j] == '\t' || map->allin[j] == ' ')
				j++;
			if (map->allin[j] == '\n' || map->allin[j] == '\0')
			{
				printf("Error: empty line\n");
				exit(1);
			}
		}
		i++;
	}
	if (map->check.player != 1)
	{
		printf("Error: player not found\n");
		exit(1);
	}
}
void	check_first_lat_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t')
		{
			printf("Error: Nuh uh ;)\n");
			exit(1);
		}
		i++;
	}
}
int	height_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	the_first_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '1')
		return (i);
	else
		return (-1);
}
int	the_last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	i--;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '1')
		return (i);
	else
		return (-1);
}
void	check_if_its_valide(t_map *map)
{
	int	i;
	int	j;
	int	height;
	int	a;
	int	b;
	int	x;
	int	y;

	i = 0;
	j = 0;
	a = 0;
	b = 0;
	x = 0;
	y = 0;
	height = height_count(map->map);
	while (map->map[i])
	{
		if (i == 0)
		{
			check_first_lat_line(map->map[i]);
		}
		else if (i == height - 1)
		{
			check_first_lat_line(map->map[i]);
		}
		else
		{
			a = the_first_char(map->map[i]);
			b = the_last_char(map->map[i]);
			if (a == -1 || b == -1)
			{
				printf("Error: Nuh uh1 ;)\n");
				exit(1);
			}
			a++;
			b--;
			while (a <= b)
			{
				if (map->map[i][a] == '0')
				{
					x = the_last_char(map->map[i - 1]);
					y = the_last_char(map->map[i + 1]);
					if (a > x)
					{
						printf("Error: Nuh uh6 ;)\n");
						exit(1);
					}
					else if (a > y)
					{
						printf("Error: Nuh uh7 ;)\n");
						exit(1);
					}
					else if (map->map[i - 1][a] == ' ' || map->map[i
							- 1][a] == '\t')
					{
						printf("Error: Nuh uh2 ;)\n");
						exit(1);
					}
					else if (map->map[i + 1][a] == ' ' || map->map[i
							+ 1][a] == '\t')
					{
						printf("Error: Nuh uh3 ;)\n");
						exit(1);
					}
					else if (map->map[i][a - 1] == ' ' || map->map[i][a
							- 1] == '\t')
					{
						printf("Error: Nuh uh 4;)\n");
						exit(1);
					}
					else if (map->map[i][a + 1] == ' ' || map->map[i][a
							+ 1] == '\t')
					{
						printf("Error: Nuh uh5 ;)\n");
						exit(1);
					}
				}
				a++;
			}
			a = 0;
			b = 0;
		}
		i++;
	}
}

void	parse_cub3d_file(char *filename)
{
	t_map	map;
	int		x;

	x = 0;
	init_map(&map);
	map.fd = open(filename, O_RDONLY);
	if (map.fd == -1)
	{
		printf("Error: failed to open file\n");
		return ;
	}
	while ((map.line = get_next_line(map.fd)))
	{
		x = direction_take(&map);
		if (x == 1)
		{
			
			map.xpm = open(map.no, O_RDONLY);
			
			//map.xpm = open("l.xpm", O_RDONLY);
					
			if (map.xpm == -1)
			{
				printf("Error: failed to open NO texture\n");
				exit(1);
			}
			else
			{
				if(ft_strlen(map.no) < 5)
				{
					printf("Error: NO texture is not a .xpm file\n");
					exit(1);
				}
				if(ft_strncmp(map.no + ft_strlen(map.no) - 4, ".xpm", 4) != 0)
				{
					printf("Error: NO texture is not a .xpm file\n");
					exit(1);
				}
				close(map.xpm);
			}
			map.xpm = open(map.so, O_RDONLY);
			if (map.xpm == -1)
			{
				printf("Error: failed to open SO texture\n");
				exit(1);
			}
			else
			{
				if(ft_strlen(map.so) < 5)
				{
					printf("Error: SO texture is not a .xpm file\n");
					exit(1);
				}
				if(ft_strncmp(map.so + ft_strlen(map.so) - 4, ".xpm", 4) != 0)
				{
					printf("Error: SO texture is not a .xpm file\n");
					exit(1);
				}
				close(map.xpm);
			}
			map.xpm = open(map.we, O_RDONLY);
			if (map.xpm == -1)
			{
				printf("Error: failed to open WE texture\n");
				exit(1);
			}
			else
			{
				if(ft_strlen(map.we) < 5)
				{
					printf("Error: WE texture is not a .xpm file\n");
					exit(1);
				}
				if(ft_strncmp(map.we + ft_strlen(map.we) - 4, ".xpm", 4) != 0)
				{
					printf("Error: WE texture is not a .xpm file\n");
					exit(1);
				}
				close(map.xpm);
			}
			map.xpm = open(map.ea, O_RDONLY);
			if (map.xpm == -1)
			{
				printf("Error: failed to open EA texture\n");
				exit(1);
			}
			else
			{
				if(ft_strlen(map.ea) < 5)
				{
					printf("Error: EA texture is not a .xpm file\n");
					exit(1);
				}
				if(ft_strncmp(map.ea + ft_strlen(map.ea) - 4, ".xpm", 4) != 0)
				{
					printf("Error: EA texture is not a .xpm file\n");
					exit(1);
				}
				close(map.xpm);
			}
			
			
			
			break ;
		}
			
		free(map.line);
	}
	if (x == 1)
	{
		//free(map.line);
		//printf("------>%s\n", map.line);
		map.allin = ft_strdup(map.line);
		free(map.line);
		while ((map.line = get_next_line(map.fd)))
		{
			map.allin = ft_strjoin1(map.allin, map.line);
			free(map.line);
		}
		check_the_map(&map);
		map.map = ft_split(map.allin, '\n');
		free(map.allin);
		check_if_its_valide(&map);
		start(&map);
	}
	else
	{
		printf("Error: invalid map\n");
		exit(1);
	}

	
	close(map.fd);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		check_format(argv[1]);
		parse_cub3d_file(argv[1]);
	}
	else
		printf("Error: invalid arguments\n");
	return (0);
}
