/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:11:39 by zerudo            #+#    #+#             */
/*   Updated: 2022/02/09 17:06:16 by zerudo           ###   ########.fr       */
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
	int	ret;

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
	if (stock && stock[0])
		return (stock);
	free(stock);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	//char		*buf;
	static char	*stock[10000]; //char ? int ? 1024?
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!*stock || is_line(stock[fd]) == 0)
		stock[fd] = save(buf, stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	line = getline_cutline(stock[fd], 1);
	stock[fd] = getline_cutline(stock[fd], 2);
	return (line);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*str1;
	char	*str2;
	char	*str3;
	int		fd1;
	int		fd2;
	int		fd3;
	int		i;

	i = 1;
	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);
	if (fd1 == - 1 || fd2 == - 1 || fd2 == 3)
	{
		printf("fucking failed to open, the very first step T_T");
		return (0);
	}
	printf("BUFFER_SIZE = %d\n\n", BUFFER_SIZE);
	while (i < 11)
	{
		str1 = get_next_line(fd1);
		str2 = get_next_line(fd2);
		str3 = get_next_line(fd3);
		printf("Line nbr n°%i de str1: %s \n", i, str1);
		printf("Line nbr n°%i de str2: %s \n", i, str2);
		printf("Line nbr n°%i de str3: %s \n", i, str3);
		i++;
		free(str1);
		free(str2);
		free(str3);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
