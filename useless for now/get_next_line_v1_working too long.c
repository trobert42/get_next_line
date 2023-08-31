/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v1_working too long.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:11:39 by zerudo            #+#    #+#             */
/*   Updated: 2022/02/10 19:09:33 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

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
	char	*line;

	i = 0;
	while (str[i] != '\n' && i < ft_strlen(str))
		i++;
	line = ft_substr(str, 0, i + 1);
	return (line);
}

void	ft_cut(char *buf)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (buf[i] != '\n' && i <ft_strlen(buf))
		i++;
	i++;
	while (j < ft_strlen(buf))
	{
		buf[j++] = buf[i++];
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUF_SIZE + 1];
	int			ret;
	char		*line;
	char		*new_line;

	ret = 0;
	line = NULL;
	if (ft_strchr(buf, 10) == 0)
	{
		if (buf[0] != '\0')
			line = ft_strdup(buf);
		while ((ret = read(fd, buf, BUF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			if (line == NULL)
				line = ft_strdup(buf);
			else
			line = ft_strjoin(line, buf);
			if (ft_strchr(line, 10) != 0)
			{
				new_line = ft_getline(line);
				free(line);
				ft_cut(buf);
				return (new_line);
			}
		}
		if (ret == 0 && buf[0] == '\0')
			return (0);
		else
		{
			ft_bzero(buf, BUF_SIZE);
			return (line);
		}
	}
	else if (ft_strchr(buf, 10) != 0)
	{
		line = ft_getline(buf);
		ft_cut(buf);
	}
	return (line);
}

/*
int	main(void)
{
	char	*str;
	int		fd;
	int		i;

	i = 1;
	fd = open("41_with_nl", O_RDONLY);
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
}*/
