#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>

#define BUFSZ1 256
#define BUFSZ2 512
#define BUFSZ3 576

int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	ssize_t bytes;
	struct iovec iov[3]; /* I/O vector */
	char buf1[BUFSZ1+1], buf2[BUFSZ2+1], buf3[BUFSZ3+1];
	
	if (argc >1)
		fname = argv[1];
	else
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return -1;
	}

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "open() failed, errno=%d\n", errno);
		return -2;
	}

	memset(buf1, 0, BUFSZ1);
	memset(buf2, 0, BUFSZ2);
	memset(buf3, 0, BUFSZ3);

	iov[0].iov_base = buf1;
	iov[0].iov_len = BUFSZ1;
	iov[1].iov_base = buf2;
	iov[1].iov_len = BUFSZ2;
	iov[2].iov_base = buf3;
	iov[2].iov_len = BUFSZ3;

	/* Perform the vectored I/O */
	bytes = readv(fd, iov, 3);
	if ( bytes == -1 )
	{
		fprintf(stderr, "readv() failed, errno=%d\n", errno);
		close(fd);
		return -3;
	}

	fprintf(stdout, "%ld bytes were read\n", bytes);

	buf1[BUFSZ1] = '\0';
	buf2[BUFSZ2] = '\0';
	buf3[BUFSZ3] = '\0';

	fprintf(stdout, "buf1:%s\n", buf1);
	fprintf(stdout, "buf2:%s\n", buf2);
	fprintf(stdout, "buf3:%s\n", buf3);

	close(fd);
	return 0;
}


