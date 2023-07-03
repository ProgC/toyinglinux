#ifndef SOLARIS
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> /* memset */
#include <stdlib.h> /* atoi, posix_memalign */
#include <sys/time.h> /* gettimeofday() */

#ifdef SOLARIS
#include <sys/fcntl.h>
#endif

#define BUFSZ (4*1024)
#define DEFBLKCNT 24

#ifdef LINUX
char *buf = NULL;
#else
char buf[BUFSZ]; /* output buffer */
#endif

int main(int argc, char *argv[])
{
	char *fname;
	int fd;
	ssize_t bytes;
	size_t count;
	int isdirectio = 1; /* 1 - use direct I/O, 0 no direct I/O */
	int blocks = DEFBLKCNT;
	int oflags;
	char ch;
	int i, j, k;
	struct timeval tm1, tm2;
	int ret;
	char *bufadr;

	if ( argc > 1 )
		fname = argv[1];
	else
	{
		fprintf(stderr, "Usage: %s filename [0|1 (direct I/O)] [blocks]\n", argv[0]);
		return -1;
	}

	if ( argc > 2 )
	{
		isdirectio = atoi(argv[2]);
		if (isdirectio != 1)
			isdirectio = 0;
	}

	if ( argc > 3 )
	{
		blocks = atoi(argv[3]);
		if (blocks <= 0)
			blocks = DEFBLKCNT;
	}

	fprintf(stdout, "Writing %u %4u-byte blocks to file %s, directio=%d\n",
			blocks, BUFSZ, fname, isdirectio);

	/* If on Linux, allocate aligned memory for the buffer */
#ifdef LINUX
#define _XOPEN_SOURCE 600
	ret = posix_memalign((void**)&buf, 512, BUFSZ);
	if (ret != 0)
	{
		fprintf(stderr, "posix_memalign() failed, ret=%d\n", ret);
		return -2;
	}
#endif
	
	/* Open the output file. Create it if it does not exist */
#ifdef SOLARIS
	if (isdirectio)
		oflags = (O_WRONLY | O_CREAT | O_TRUNC | O_DSYNC);
	else
		oflags = (O_WRONLY | O_CREAT | O_TRUNC);
#else
#ifdef __APPLE__
	oflags = (O_WRONLY|O_CREAT|O_TRUNC);
#else
	/* for linux, aix and others */
	if (isdirectio)
		oflags = (O_WRONLY|O_CREAT|O_TRUNC|O_DIRECT);
	else
		oflags = (O_WRONLY|O_CREAT|O_TRUNC);
#endif
#endif

	fd = open(fname, oflags, 0664);
	if (fd == -1)
	{
		fprintf(stderr, "open() failed, error=%d\n", errno);
		return -3;
	}

	
#ifdef SOLARIS
	if (isdirectio)
		ret = directio(fd, DIRECTIO_ON);
	else
		ret = directio(fd, DIRECTIO_OFF);
	
	if (ret != 0)
	{
		fpritnf(stderr, "directio() failed, errno=%d\n", errno);
		close(fd);
		return -4;
	}
#endif

#ifdef __APPLE__
	if (isdirectio)
		ret = fcntl(fd, F_NOCACHE, 1); /* turns data caching off */
	else
		ret = fcntl(fd, F_NOCACHE, 0); /* turns data caching on */

	if (ret == -1)
	{
		fprintf(stderr, "fcntl() failed, errno=%d\n", errno);
		close(fd);
		return -4;
	}
#endif

	ret = gettimeofday(&tm1, (void*)NULL);

	/* Write the number of blocks specified */
	for ( k = 0; k < blocks; k++ )
	{
		i = k % 26;
		ch = 'A' + i;

		/* Fill the buffer with message to write */
		for ( j = 0; j < BUFSZ; j++ )
			buf[j] = ch;

		/* Write the contents of the buffer to the file.
		 * This will overwrite the beginning of the file if it already exists.
		 */

		count = BUFSZ;
		bufadr = buf;
		while( count > 0)
		{
			errno = 0;
			bytes = write(fd, bufadr, count);
			if ( bytes == -1 )
			{
				fprintf(stderr, "write() failed, errno=%d\n", errno);
				close(fd);
				return -5;
			}
			count = count - bytes;
			bufadr = bufadr + bytes;
		}
	}

	ret = gettimeofday(&tm2, (void*)NULL);
	printf("String time : %010ld:%010u\n", tm1.tv_sec, tm1.tv_usec);
	printf("End    time : %010ld:%010u\n", tm2.tv_sec, tm2.tv_usec);

	close(fd);
	return 0;
}


