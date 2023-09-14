/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:05:24 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 15:31:10 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_coin(t_list *so_long)
{
	if (so_long->map[so_long->position[Y] / 50]
		[so_long->position[X] / 50] == 'C')
	{
		so_long->map[so_long->position[Y] / 50]
		[so_long->position[X] / 50] = '0';
		so_long->coin_count--;
	}
}

void	cheack_win_condition(t_list *so_long)
{
	if (so_long->coin_count == 0 && so_long->map[so_long->position[Y] / 50]
		[so_long->position[X] / 50] == 'E')
	{
		write(1, "Congratulations! You collected ", 32);
		write(1, "all the coins and reached the exit!\n", 37);
		exit(0);
	}
}

int	hook(int keycode, t_list *so_long)
{
	if (keycode == 53)
	{
		mlx_hook (so_long->win, ON_DESTROY, 1 << 0, ft_close, NULL);
		exit(0);
	}
	if (keycode == 124)
		move_right(so_long);
	if (keycode == 123)
		move_left(so_long);
	if (keycode == 125)
		move_down(so_long);
	if (keycode == 126)
		move_up(so_long);
	collect_coin(so_long);
	cheack_win_condition(so_long);
	write(1, "movement: ", 10);
	ft_putnbr(so_long->moves);
	write(1, "\n", 1);
	return (1);
}
