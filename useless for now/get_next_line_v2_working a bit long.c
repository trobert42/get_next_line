/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2_working a bit long.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:11:39 by zerudo            #+#    #+#             */
/*   Updated: 2021/12/18 10:33:08 by zerudo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUF_SIZE
# define BUF_SIZE 42
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

char	*ft_getline(char *str, char	*buf)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\n' && i < ft_strlen(str))
		i++;
	line = ft_substr(str, 0, i + 1);
	ft_cut(buf);
	return (line);
}

void	ft_cut(char *buf)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (buf[i] != '\n' && i < ft_strlen(buf))
		i++;
	i++;
	while (j < ft_strlen(buf))
	{
		buf[j++] = buf[i++];
	}
}

char	*find_and_get(char *buf, char *line)
{
	char	*new_line;
	char	*temp;

	if (line == NULL)
		temp = strdup(buf);
	else
	{
		temp = ft_strjoin(line, buf);
		free (line);
	}
	if (ft_strchr(temp, 10) != 0)
	{
		new_line = ft_getline(temp, buf);
		free(temp);
		return (new_line);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	buf[BUF_SIZE + 1];
	int			ret;
	char		*line;

	ret = 0;
	line = NULL;
	if (ft_strchr(buf, 10) != 0)
	{
		line = ft_getline(buf, buf);
		return (line);
	}
	if (buf[0] != '\0')
		line = ft_strdup(buf);
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		line = find_and_get(buf, line);
		if (ft_strchr(line, 10) != 0)
			return (line);
	}
	if (line == NULL)
		return (0);
	ft_bzero(buf, BUF_SIZE);
	return (line);
}

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
