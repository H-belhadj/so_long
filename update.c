/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 08:43:43 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 14:50:16 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_small(t_list *so_long, t_value *value, int i)
{
	value->i = 0;
	while (so_long->map[i][value->i])
	{
		if (so_long->map[i][value->i] != '1')
		{
			write(2, "ERROR: The map must be surrounded by walls.\n", 45);
			exit(1);
		}
		value->i++;
	}
	return (0);
}

void	process_tile(t_list *so_long, int i, int j)
{
	if (so_long->map[i][j] == '0')
		mlx_put_image_to_window(so_long->mlx, so_long->win,
			so_long->backgound, j * 50, i * 50);
	if (so_long->map[i][j] == '1')
		mlx_put_image_to_window(so_long->mlx, so_long->win,
			so_long->wll, j * 50, i * 50);
	if (so_long->map[i][j] == 'C')
		mlx_put_image_to_window(so_long->mlx, so_long->win,
			so_long->coins, j * 50, i * 50);
	if (so_long->map[i][j] == 'E')
	{
		mlx_put_image_to_window(so_long->mlx, so_long->win,
			so_long->backgound, j * 50, i * 50);
		mlx_put_image_to_window(so_long->mlx, so_long->win,
			so_long->door, j * 50, i * 50);
	}
	if (so_long->map[i][j] == 'P')
		mlx_put_image_to_window(so_long->mlx, so_long->win,
			so_long->backgound, j * 50, i * 50);
}

void	short_update(t_list *so_long, int *i, int *j)
{
	while (so_long->map[++(*i)])
	{
		*j = -1;
		while (so_long->map[(*i)][++(*j)])
			process_tile(so_long, *i, *j);
	}
}

int	update(t_list *so_long)
{
	int		i;
	int		j;

	i = -1;
	short_update(so_long, &i, &j);
	mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->player,
		so_long->position[X], so_long->position[Y]);
	if (so_long->coin_count == 0 && so_long->map[so_long->position[Y] / 50]
		[so_long->position[X] / 50] == 'E') 
		exit(0);
	return (0);
}
