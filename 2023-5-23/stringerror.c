#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	printf("EPERM :  %s\n", strerror(EPERM));
	exit(0);
}

