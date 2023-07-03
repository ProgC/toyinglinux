#include <stdio.h>
#include <unistd.h>

int main()
{
	char buf[128];
	long len;
	char* currentdirectory;

	len = pathconf(".", _PC_PATH_MAX);
	currentdirectory = getcwd(buf, len);
	if ( currentdirectory != NULL )
	{
		fprintf(stdout, "CurrentDirectory : %s\n", currentdirectory);
	}

	return 0;
}

