/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:11:39 by zerudo            #+#    #+#             */
/*   Updated: 2022/02/11 14:42:42 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*getline_cutline(char *str, int flag)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\n' && i < ft_strlen(str))
		i++;
	if (flag == 1)
		line = ft_substr(str, 0, i + 1);
	else
	{
		line = ft_substr(str, i + 1, ft_strlen(str));
		free(str);
	}
	return (line);
}

char	*save(char *buf, char *stock, int fd)
{
	int		ret;

	ret = 1;
	if (!stock)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buf[ret] = '\0';
		stock = ft_strdup(buf);
	}
	while (ret > 0 && is_line(stock) == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		stock = ft_strjoin(stock, buf);
	}
	if (stock[0])
		return (stock);
	free(stock);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*stock[1024];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	stock[fd] = save(buf, stock[fd], fd);
	free(buf);
	if (!stock[fd])
		return (NULL);
	line = getline_cutline(stock[fd], 1);
	stock[fd] = getline_cutline(stock[fd], 2);
	return (line);
}
