/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:35:55 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 15:20:30 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cheack_fd(int fd)
{
	if (fd == -1)
	{
		write(2, "ERROR\nMAP NOT FOUND\n", 20);
		exit(1);
	}
}

int	red_lines_1(t_value *value)
{
	int	len;

	len = ft_strlen(value->total);
	if (value->total[len] == '\n')
	{
		write(2, "ERROR: The map must be surrounded by walls.\n", 45);
		exit (1);
	}
	return (0);
}

int	read_lines(int fd, t_value *value)
{
	int		is_first_line;

	is_first_line = 1;
	while (1)
	{
		value->str = get_next_line(fd);
		if (!value->str && is_first_line)
		{
			close(fd);
			exit(write(2, "ERROR\nempty file\n", 17));
		}
		if (!value->str)
			break ;
		is_first_line = 0;
		if (value->str[0] == '\n')
			exit(1);
		value->total = ft_strjoin(value->total, value->str);
		free(value->str);
		value->cnt++;
	}
	red_lines_1(value);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list		so_long;
	t_value		value;
	int			fd;

	value.collec_count = 0;
	if (argc != 2)
		return (write(1, "ERROR: Invalid number of arguments\n", 35), 1);
	file_ber(argv);
	fd = open(argv[1], O_RDONLY);
	cheack_fd(fd);
	value.cnt = 1;
	value.total = NULL;
	read_lines(fd, &value);
	close(fd);
	if (!value.total)
		exit(1);
	split_main(&so_long, &value);
}
