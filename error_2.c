/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:26:38 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 15:21:00 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	search_player(t_list *so_long)
{
	int		i;
	int		j;

	i = -1;
	so_long->plyer_x = -1;
	so_long->plyer_y = -1;
	while (so_long->map[++i])
	{
		j = -1;
		while (so_long->map[i][++j])
		{
			if (so_long->map[i][j] == 'P')
			{
				so_long->plyer_x = j;
				so_long->plyer_y = i;
				return ;
			}
		}
	}
	if (so_long->plyer_x == -1 || so_long->plyer_y == -1)
	{
		write(1, "ERROR : NO PLYER FOUND\n", 23);
		exit(1);
	}
}

int	check_existance(char **fake_map)
{
	int		i;
	int		j;

	i = -1;
	while (fake_map[++i])
	{
		j = -1;
		while (fake_map[i][++j])
		{
			if (fake_map[i][j] == 'E')
				return (1);
			else if (fake_map[i][j] == 'C')
				return (1);
			else if (fake_map[i][j] == 'P')
				return (1);
		}
	}
	return (0);
}

void	back_track(t_list *so_long, int x, int y)
{
	if (so_long->fake_map[x][y + 1] && so_long->fake_map[x]
			[y + 1] != '\n' && so_long->fake_map[x][y + 1] != '1'
	&& so_long->fake_map[x][y + 1] != 'x')
	{
		so_long->fake_map[x][y + 1] = 'x';
		back_track(so_long, x, y + 1);
	}
	if (x - 1 >= 0 && so_long->fake_map[x - 1][y] != '1'
	&& so_long->fake_map[x - 1][y] != 'x')
	{
		so_long->fake_map[x - 1][y] = 'x';
		back_track(so_long, x - 1, y);
	}
	if (y - 1 >= 0 && so_long->fake_map[x][y - 1] != '1'
	&& so_long->fake_map[x][y - 1] != 'x')
	{
		so_long->fake_map[x][y - 1] = 'x';
		back_track(so_long, x, y - 1);
	}
	if (so_long->fake_map[x + 1] && so_long->fake_map[x + 1][y] != '1'
	&& so_long->fake_map[x + 1][y] != 'x')
	{
		so_long->fake_map[x + 1][y] = 'x';
		back_track(so_long, x + 1, y);
	}
}

void	empty_file(char *file)
{
	int		fd;
	char	*line;

	fd = open (file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		free(line);
		exit(write(2, "ERROR\nempty file\n", 17));
	}
	free(line);
	close(fd);
}

void	file_ber(char **argv)
{
	char	*extension;
	char	*map_file;

	extension = ".ber";
	map_file = argv[1];
	if (ft_strlen(map_file) < ft_strlen(extension)
		||ft_strcmp (map_file + ft_strlen(map_file) 
			- ft_strlen(extension), extension) != 0)
	{
		write(1, "ERROR: Map filename must have .ber extension\n", 45);
		exit (1);
	}
}
