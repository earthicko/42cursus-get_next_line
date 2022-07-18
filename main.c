#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include "get_next_line.h"

int main() {
    int fd[2];
    fd[0] = open("./file0", O_RDONLY);
    fd[1] = open("./file1", O_RDONLY);
    for (int i = 0; i < 10; i++) printf("line %d: %s", i, get_next_line(fd[i % 2]));
	return 0;
}
