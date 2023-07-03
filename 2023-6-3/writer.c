/* Writer process */
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ 512
#define WRITER_WAIT_TIME 4
#define LOOPCNT 5

int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	ssize_t bytes;
	char buf[BUFSZ];
	size_t i,j;

	if ( argc > 1 )
		fname = argv[1];
	else
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return -1;
	}

	/* Open a file for write only. Create it if it does not already exist.
	 * Truncate the file (erase old contents) if it already exists */

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ( fd == -1 )
	{
		fprintf(stderr, "open() failed, errno=%d\n", errno);
		return -2;
	}

	/* The write and wait loop */
	for ( i = 1; i < LOOPCNT; i++ )
	{
		/* Fill the buffer with the block number */
		for ( j = 0; j < BUFSZ; j++ )
			buf[j] = i + '0';

		/* Write the contents of the buffer to the file */
		bytes = write(fd, buf, BUFSZ);
		if ( bytes == -1 )
		{
			fprintf(stderr, "write() failed, errno=%d\n", errno);
			close(fd);
			return -3;
		}
		fprintf(stdout, "%ld bytes were written into the file\n", bytes);

		/* Wait for a few seconds so the read has a change to read it */
		sleep(WRITER_WAIT_TIME); /* which is 4 seconds */
	}

	close(fd);
	return 0;
}




