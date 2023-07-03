#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> /* memset */
#include <stdlib.h> /* atoi */

#define BUFSZ 512
#define DEFBLKCNT 62

int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	ssize_t bytes;
	size_t count;
	char buf[BUFSZ];
	int blocks = DEFBLKCNT;
	char ch;
	int i, j, k;
	char *bufadr;

	if (argc > 1)
		fname = argv[1];
	else
	{
		fprintf(stderr, "Usage: %s filename [blocks]\n", argv[0]);
		return (-1);
	}

	if (argc > 2)
	{
		blocks = atoi(argv[2]);
		if ( blocks <= 0)
			blocks = DEFBLKCNT;
	}

	fprintf(stdout, "Writing %u blocks to file %s\n", blocks, fname);

	/* Open the output file. Create it if it does not exist.
	 * Truncate the file to zero length if it already exist */

	fd = open( fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ( fd == -1 )
	{
		fprintf(stderr, "open() failed, errno=%d\n", errno);
		return (-2);
	}

	/* Write the number of blocks specified */
	for ( k = 0; k < blocks; k++ )
	{
		i = k % 62;
		if ( i < 10 )
			ch = '0' + i;
		else if ( i < 36 )
			ch = 'a' + (i - 10);
		else if ( i >= 36 )
			ch = 'A' + (i - 36);
		
		for ( j = 0; j < BUFSZ; ++j )
			buf[j] = ch;

		/* Write the contents of the buffer to the file */
		count = BUFSZ;
		bufadr = buf;
		while( count > 0 )
		{
			bytes = write(fd, bufadr, count);
			if ( bytes == -1 )
			{
				fprintf(stderr, "write() failed, errno=%d\n", errno);
				close(fd);
				return -3;
			}
			count = count - bytes;
			bufadr = bufadr + bytes;
		}
	}

	close(fd);
	return 0;
}

