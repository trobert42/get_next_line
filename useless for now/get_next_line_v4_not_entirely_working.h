/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v4_not_entirely_working.h            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:58:25 by trobert           #+#    #+#             */
/*   Updated: 2021/12/19 15:06:59 by zerudo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE
# define FT_GET_NEXT_LINE

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include "get_next_line.h"


int		is_line(const char *s);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*getline_cutline(char *str, int flag);
char	*save(char *buf, char *rest);
char	*get_next_line(int fd);

#endif
