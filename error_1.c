/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:23:24 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 14:45:17 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	walls_error(t_list *so_long, t_value *value)
{
	value->i = 0;
	while (so_long->map[value->i] != NULL) 
	{
		if (so_long->map[value->i][0] != '1' || so_long->map[value->i]
				[value->row_length - 1] != '1')
		{
			write(2, "ERROR: The map must be surrounded by walls.\n", 45);
			exit (1);
		}
		value->i++;
	}
	return (0);
}

int	walls_error_2(t_list *so_long, t_value *value)
{
	int	i;

	i = 0;
	while (so_long->map[0][i] != '\0')
	{
		if (so_long->map[0][i] != '1')
		{
			write(2, "ERROR: The map must be surrounded by walls.\n", 45);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (so_long->map[i] != '\0')
		i++;
	i--;
	ft_small(so_long, value, i);
	return (0);
}

int	char_error_1(t_list *so_long, t_value *value)
{
	value->j = 0;
	while (so_long->map[value->i][value->j])
	{
		value->allowed_char = "01CEP";
		if (!ft_strchr(value->allowed_char, so_long->map[value->i][value->j]))
		{
			write(1, "Error: ", 7);
			write(1, "The map can only contain these 5 characters: ", 46);
			write(1, "0, 1, C, E, P\n", 13);
			exit (1);
		}
		if (so_long->map[value->i][value->j] == 'E')
			value->exit_count++;
		else if (so_long->map[value->i][value->j] == 'C')
			value->collec_count++;
		else if (so_long->map[value->i][value->j] == 'P')
		{
			value->player_pos[X] = value->j * 50;
			value->player_pos[Y] = value->i * 50;
			value->start_count++;
		}
		value->j++;
	}
	return (0);
}

int	char_error(t_list *so_long, t_value *value)
{
	value->i = 0;
	while (so_long->map[value->i])
	{
		char_error_1(so_long, value);
		if (ft_strlen(so_long->map[value->i]) != value->row_length)
		{
			write(1, "ERROR: The map is not rectangular.\n", 36);
			exit (1);
		}
		value->i++;
	}
	return (0);
}

int	split_main(t_list *so_long, t_value *value)
{
	so_long->map = ft_split(value->total, '\n');
	so_long->fake_map = ft_split(value->total, '\n');
	search_player(so_long);
	back_track(so_long, so_long->plyer_x, so_long->plyer_y);
	if (check_existance(so_long->fake_map) == 1)
	{
		write(1, "Error\n invalid path\n", 21);
		exit (1);
	}
	free_2d (so_long->fake_map);
	so_long->moves = 0;
	value->i = 0;
	value->exit_count = 0;
	value->start_count = 0;
	value->row_length = ft_strlen(so_long->map[0]);
	char_error(so_long, value);
	so_long->coin_count = value->collec_count;
	walls_error(so_long, value);
	walls_error_2(so_long, value);
	start_end_error(value);
	write(1, "YOUR MAP IS GOOD\n", 17);
	short_main(so_long, value);
	return (0);
}
