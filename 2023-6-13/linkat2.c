#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h> /* link() */
#include <fcntl.h> /* open(), AT_FDCWD */
#include <sys/stat.h>
#include <string.h> /* strcat() */

int main(int argc, char *argv[])
{
	int ret;
	int fd;
	int flags = 0; /* in linkat.c it used to be AT_SYMLINK_FOLLOW */
	char *fname = NULL;
	char linkname[128];

	if ( argc <= 1 )
	{
		fprintf(stdout, "Usage: %s existing_file_name\n", argv[0] );
		return -1;
	}

	fname = argv[1];
	fprintf(stdout, "Creating two links to the file %s...\n", fname);

	/* Open current directory */
	fd = open(".", 0);
	if ( fd < 0 )
	{
		fprintf(stderr, "open() failed, errno=%d\n", errno);
		return -2;
	}

	/* Create the first link */
	strcpy(linkname, fname);
	strcat(linkname, "_link1");
	ret = link(fname, linkname);

	if ( ret < 0 )
	{
		fprintf(stderr, "First link() failed, errno=%d\n", errno);
		return -3;
	}

	strcat(linkname, "_link2");
	ret = linkat(fd, fname, fd, linkname, flags);
	if ( ret == -1 )
	{
		fprintf(stderr, "linkat() failed, errno=%d\n", errno);
		return -4;
	}

	return 0;
}



