#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int res = mkfifo("/tmp/my_fifo", 0777);
	if ( res == 0 )
		printf("FIFO Created\n");
	exit(EXIT_SUCCESS);
}
