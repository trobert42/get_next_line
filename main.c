#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int main (int ac, char *av[]) {
	if (ac != 2)
		return (printf("wrong nb of args\n"), 1);
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("can't open\n"), 1);
	char *str;
	while ((str = get_next_line(fd)) != NULL) {
		printf("%s \n", str);
		free(str);
	}
	return 0;
}