#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ 30
#define READER_WAIT_TIME 1
#define LOOPCNT 5


int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	ssize_t bytes;
	char buf[BUFSZ+1];
	size_t i, j;

	/* Expect to get the file name from user */
	if ( argc > 1 )
		fname = argv[1];
	else
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return -1;
	}

	fd = open(fname, O_RDONLY);
	if ( fd == -1 )
	{
		fprintf(stderr, "open() failed, errno=%d\n", errno);
		return -2;
	}

	/* read some data from the file */
	bytes = read(fd, buf, BUFSZ);
	if ( bytes == -1 )
	{
		fprintf(stderr, "read() failed, errno=%d\n", errno);
		close(fd);
		return -3;
	}

	buf[bytes] = '\0';
	fprintf(stdout, "Just read the following %ld bytes from the file %s:\%s\n", bytes, fname, buf);

	close(fd);
	return 0;
}


