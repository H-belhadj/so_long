/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:29:01 by hbelhadj          #+#    #+#             */
/*   Updated: 2023/09/11 09:45:07 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*final;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	final = 0;
	line = read_fd(fd, line);
	if (!line)
		return (0);
	final = ft_before_line(line);
	line = ft_after_line(line);
	return (final);
}

int	new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_fd(int fd, char *line)
{
	char	*buff;
	int		counter;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	counter = 1;
	while (counter)
	{
		counter = read(fd, buff, BUFFER_SIZE);
		if (counter < 0)
		{
			free(buff);
			free(line);
			return (0);
		}
		buff[counter] = '\0';
		line = ft_strjoin(line, buff);
		if (new_line(line) == 1)
			break ;
	}
	free(buff);
	return (line);
}

char	*ft_before_line(char *line)
{
	char	*str;
	int		i;

	i = 0;
	if (line[0] == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_after_line(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (0);
	}
	str = malloc(ft_strlen(line) - i + 1);
	if (!str)
		return (0);
	i++;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}
