#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include "get_next_line.h"

int main() {
    int fd = open("./file0", O_RDONLY);
    for (int i = 0; i < 10; i++) printf("line %d: %s", i, get_next_line(fd));
	return 0;
}
