#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ 512
#define READER_WAIT_TIME 1
#define LOOPCNT 5

int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	ssize_t bytes;
	size_t count;
	char buf[BUFSZ+1];
	size_t i, j;
	char *bufadr;

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

	/* The read loop */
	for ( i = 1; i < LOOPCNT; i++ )
	{
		/* Read a block at each iteration */
		count = BUFSZ;
		bufadr = buf;
		fprintf(stdout, "read start...\n");
		while(count > 0)
		{
			bytes = read(fd, bufadr, count);

			if ( bytes == -1 )
			{
				fprintf(stderr, "read() failed, errno=%d\n", errno);
				close(fd);
				return -3;
			}
			else if ( bytes > 0 )
			{
				fprintf(stdout, "%ld ", bytes );
			}

			count = count - bytes;
			bufadr = bufadr + bytes;
		}
		buf[BUFSZ] = '\0';
		fprintf(stdout, "Just read the following block:\n%s\n", buf);
	}

	close(fd);
	return 0;
}


