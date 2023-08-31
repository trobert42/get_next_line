/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:11:39 by zerudo            #+#    #+#             */
/*   Updated: 2021/12/19 18:21:07 by zerudo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUF_SIZE
# define BUF_SIZE 100
#endif

char	*getline_cutline(char *str, int flag)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\n' && i < ft_strlen(str))
		i++;
	if (flag == 1)
	{
		line = ft_substr(str, 0, i + 1);
		free(str);
	}
	else
		line = ft_substr(str, i + 1, ft_strlen(str));
	return (line);
}

char	*save(char *buf, char *rest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!rest && is_line(buf) == 1)
		rest = getline_cutline(buf, 2);
	else if (rest)
	{
		while (rest[i] != '\n' && i < ft_strlen(rest))
			i++;
		if (i < ft_strlen(rest))
			i++;
		while (j < ft_strlen(rest))
			rest[j++] = rest[i++];
		rest = ft_strjoin(rest, buf);
	}
	if (rest && !rest[0])
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*find_and_get(char *buf, char *line, char *rest)
{
	char	*new_line;
	char	*temp;

	if (!line && rest)
		temp = ft_strdup(rest);
	else if (!line && !rest)
		temp = ft_strdup(buf);
	else if (line && !rest)
		temp = ft_strjoin(line, buf);
	if (rest && buf && !temp)
		temp = ft_strjoin(rest, buf);
	free (line);
	if (is_line(temp) == 0)
		return (temp);
	new_line = getline_cutline(temp, 1);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		buf[BUF_SIZE + 1];
	int			ret;
	static char	*rest = NULL;
	char		*line;

	if (fd < 0 || BUF_SIZE <= 1)
		return (NULL);
	line = NULL;
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	while (ret > 0 || rest != 0)
	{
		line = find_and_get(buf, line, rest);
		rest = save(buf, rest);
		if (is_line(line) == 1)
			return (line);
		ret = read(fd, buf, BUF_SIZE);
		buf[ret] = '\0';
	}
	if (!line)
		return (0);
	return (getline_cutline(line, 1));
}
/*
int	main(void)
{
	char	*str;
	int		fd;
	int		i;

	i = 1;
	fd = open("text.txt", O_RDONLY);
	if (fd == - 1)
	{
		printf("fucking failed to open, the very first step T_T");
		return (0);
	}
	printf("BUF_SIZE = %d\n\n", BUF_SIZE);
	while (i < 11)
	{
		str = get_next_line(fd);
		printf("Line nbr n°%i: %s \n", i, str);
		i++;
		free(str);
	}
	close(fd);
	return (0);
}*/
