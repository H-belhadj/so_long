/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:57:15 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 14:55:02 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	protect_image(t_list *so_long, t_value *value)
{
	so_long->win = mlx_new_window(so_long->mlx,
			ft_strlen(so_long->map[0]) * 50, (value->cnt - 1) * 50, "so_long");
	if (!so_long->win)
		exit (1);
	so_long->wll = mlx_xpm_file_to_image(so_long->mlx,
			"textures/wall.xpm", &value->high, &value->width);
	if (!so_long->wll)
		exit (1);
	so_long->door = mlx_xpm_file_to_image(so_long->mlx,
			"textures/door.xpm", &value->high, &value->width);
	if (!so_long->door)
		exit (1);
	so_long->player = mlx_xpm_file_to_image(so_long->mlx,
			"textures/player.xpm", &value->high, &value->width);
	if (!so_long->player)
		exit (1);
	so_long->coins = mlx_xpm_file_to_image(so_long->mlx,
			"textures/coin.xpm", &value->high, &value->width);
	if (!so_long->coins)
		exit (1);
	so_long->backgound = mlx_xpm_file_to_image(so_long->mlx,
			"textures/backgound.xpm", &value->high, &value->width);
	if (!so_long->backgound)
		exit (1);
}

int	ft_close(void)
{
	exit(1);
	return (0);
}

void	short_main(t_list *so_long, t_value *value)
{
	value->high = 50;
	value->width = 50;
	so_long->mlx = mlx_init();
	protect_image(so_long, value);
	so_long->position[X] = value->player_pos[X];
	so_long->position[Y] = value->player_pos[Y];
	mlx_hook (so_long->win, ON_KEYDOWN, 1 << 0, hook, so_long);
	mlx_hook (so_long->win, ON_DESTROY, 1 << 0, ft_close, NULL);
	mlx_loop_hook (so_long->mlx, update, so_long);
	mlx_loop (so_long->mlx);
}

int	start_end_error(t_value *value)
{
	if (value->exit_count != 1 || value->collec_count < 1 
		|| value->start_count != 1) 
	{
		write(1, "ERROR: The map must contain 1 exit, at least 1", 40);
		write(1, " collectible, and 1 starting position to be valid.\n", 47);
		exit (1);
	}
	return (0);
}
