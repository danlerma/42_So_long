/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:03:43 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/11/08 13:58:54 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	objs_and_square(char *line, size_t len, t_map *map)
{
	size_t	i;

	i = 0;
	if (line[i] != '1' || line[len - 1] != '1')
		print_error("LOS MUROS NO SON VÁLIDOS\n");
	while (line[i])
	{
		check_objects(line[i], &map->objects);
		if (line[i] == '\n')
			break ;
		if (line [i] != '0' && line [i] != '1' && line [i] != 'C'
			&& line [i] != 'E' && line [i] != 'P')
			print_error("LOS OBJETOS NO SON VÁLIDOS\n");
		i++;
	}
	if (len != i)
		print_error("MAPA NO VÁLIDO\n");
}

void	check_map(int fd, t_map *map)
{
	char	*line;
	size_t	i;

	line = get_next_line(fd);
	if (line == NULL)
		print_error("ARCHIVO VACIO\n");
	init_objs(map);
	map->nchars = ft_strlen(line) - 1;
	i = 1;
	while (line)
	{	
		objs_and_square(line, map->nchars, map);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map->nrows = i - 1;
	if (map->objects.floor == 0 || map->objects.character != 1
		|| map->objects.exit != 1 || map->objects.collect < 1)
		print_error("HAS METIDO OBJETOS DE MAS\n");
}

int	check_argument(char *argv)
{
	char	*point;
	int		fd;

	point = ft_strchr(argv, '.');
	if (point == NULL || ft_strncmp(point, ".ber", 4) != 0)
		print_error("EXTENSION NO VALIDA\n");
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		print_error("ERROR AL ABRIR EL ARCHIVO\n");
	return (fd);
}

void	save_map(int fd, t_map *map)
{
	char	*line;
	char	**archive;
	int		i;
		
	line = get_next_line(fd);
	archive = malloc(map->nrows * sizeof(char *));
	if (archive == NULL)
		print_error("CALLOC ES NULO\n");
	i = -1;
	while (line)
	{	
		if (line != NULL)
		{
			archive[++i] = ft_strdup(line);
			if (archive[i] == NULL)
				print_error("ARCHIVE MAL\n");
		}
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (++i < (int)map->nchars)
		if (archive[0][i] != '1' || archive[map->nrows - 1][i] != '1')
			print_error("EL PRIMERO O EL ULTIMO\n");
}
