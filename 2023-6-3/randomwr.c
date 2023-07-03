#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ 512

int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	off_t offset, offset_ret;
	ssize_t bytes;
	size_t count;
	char buf[BUFSZ];

	if ( argc > 1 )
		fname = argv[1];
	else
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return -1;
	}

	/* Open a file for write only. This open() will fail with errno = 2
	 * if the file does not exist */

	fd = open(fname, O_WRONLY, 0644);
	if (fd == -1)
	{
		fprintf(stderr, "open() failed, errno=%d\n", errno);
		return -2;
	}

	/* Write 5 bytes starting at file offset 512 */
	offset = 512;
	offset_ret = lseek(fd, offset, SEEK_CUR);

	if ( offset_ret == -1 )
	{
		fprintf(stderr, "lseek() failed, errno=%d\n", errno);
		close(fd);
		return 3;
	}

	fprintf(stdout, "offset_ret = %lld \n", offset_ret);

	for ( count = 0; count < 5; count++)
		buf[count] = 'A';

	bytes = write(fd, buf, 5);
	if ( bytes == -1 )
	{
		fprintf(stderr, "write() failed, errno=%d\n", errno);
		close(fd);
		return -4;
	}

	/* Write another 5 bytes starting at file offset 1024 */
	offset = 1024;
	offset_ret = lseek(fd, offset, SEEK_SET);
	if (offset_ret == -1)
	{
		fprintf(stderr, "lseek() failed, errno=%d\n", errno);
		close(fd);
		return -5;
	}

	fprintf(stdout, "offset_ret = %lld \n", offset_ret);

	for (count = 0; count < 5; count++ )
		buf[count] = 'B';

	bytes = write(fd, buf, 5);
	if (bytes == -1)
	{
		fprintf(stderr, "write() failed, errno=%d\n", errno);
		close(fd);
		return -6;
	}

	close(fd);
	return 0;
}


