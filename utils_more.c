/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:47:01 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/14 15:27:12 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (str);
}

void	ft_putnbr(int num)
{
	char	*str;

	str = "0123456789";
	if (num > 9)
		ft_putnbr(num / 10);
	write(1, &str[num % 10], 1);
}

void	free_2d(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
		free(m[i]);
	free(m);
}
