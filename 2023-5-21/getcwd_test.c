#include <unistd.h>
#include <stdio.h>

int main()
{
	char buf[128];
	getcwd(buf, 128);
	printf("current dir : %s\n", buf);
}

