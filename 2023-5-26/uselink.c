#include <stdio.h>
#include <errno.h>

/* use static library */

int main(int argc, char *argv[])
{
	int ret;
	int x = 22;
	char *mymsg = "Hello, there!";

	ret = tripleIt(x);
	printf("Triple of %d is %d\n", x, ret);

	ret = echoMsg(mymsg);
	printf("There are %d characters in the string '%s'\n", ret, mymsg);
	return 0;
}


