/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:22:53 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/13 10:11:35 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_right(t_list *so_long)
{
	if (so_long->map[so_long->position[Y] / 50]
		[so_long->position[X] / 50 + 1] != '1')
	{
		so_long->position[X] += 50;
		so_long->moves++;
	}
}

void	move_left(t_list *so_long)
{
	if (so_long->map[so_long->position[Y] / 50]
		[so_long->position[X] / 50 - 1] != '1')
	{
		so_long->position[X] -= 50;
		so_long->moves++;
	}
}

void	move_down(t_list *so_long)
{
	if (so_long->map[so_long->position[Y] / 50 + 1]
		[so_long->position[X] / 50] != '1')
	{
		so_long->position[Y] += 50;
		so_long->moves++;
	}
}

void	move_up(t_list *so_long)
{
	if (so_long->map[so_long->position[Y] / 50 - 1]
		[so_long->position[X] / 50] != '1')
	{
		so_long->position[Y] -= 50;
		so_long->moves++;
	}
}
