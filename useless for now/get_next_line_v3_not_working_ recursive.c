/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v3_not_working_ recursive.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:11:39 by zerudo            #+#    #+#             */
/*   Updated: 2022/02/11 16:26:02 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUF_SIZE
# define BUF_SIZE 3
#endif

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = '\0';
		i++;
	}
}

char	*ft_getline(char *str)
{
	int		i;
//	int		j;
	char	*line;

	i = 0;
	while (str[i] != '\n' && i < ft_strlen(str))
		i++;
	line = ft_substr(str, 0, i + 1);
/*	i = 0;
	j = 0;
	while (buf[i] != '\n' && i < ft_strlen(buf))
		i++;
	i++;
	while (j < ft_strlen(buf))
		rest[j++] = buf[i++];
	rest = ft_substr(buf, i, ft_strlen(buf));*/
	return (line);
}

char	*ft_cut(char *buf, char *rest)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && i < ft_strlen(buf))
		i++;
	i++;
	rest = ft_substr(buf, i, ft_strlen(buf));
	return(rest);
}

char	*find_and_get(char *buf, char *line, char *rest)
{
	char	*new_line;
	char	*temp;

	if (!line && rest == NULL)
		temp = ft_strdup(buf);
	else if (!rest)
		temp = ft_strdup(rest);
	else
	{
		temp = ft_strjoin(line, buf);
		free (line);
	}
	if (is_line(temp) == 1)
	{
		new_line = ft_getline(temp);
		rest = ft_cut(buf, rest);
		free (temp);
		return (new_line);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char	buf[BUF_SIZE + 1];
	char	*line;
	static char *rest;
	int	ret;

	line = NULL;
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	if (ret > 0)
	{
		line = find_and_get(buf, line, rest);
		if (is_line(line) == 1)
			return (line);
		else
		{
			line = ft_strjoin(line, get_next_line(fd));
			line = find_and_get(buf, line, rest);
			return (line);
		}
	}
	if (buf[0] == '\0')//rest est nul ?
		return (0);
	else
	{
		return (line = ft_getline(line));
	}
	return (0);
}

int	main()
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
	while (i < 4)
	{
		str = get_next_line(fd);
		printf("Line nbr n°%i: %s \n", i, str);
		i++;
		free(str);
	}
	close(fd);
	return (0);
}
