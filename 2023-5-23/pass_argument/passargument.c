#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("process option and arguments\n");

	for ( int i = 1; i < argc; ++i )
	{
		if ( argv[i][0] == '-' )
		{
			printf("Option : %s\n", argv[i] + 1);
		}
		else
		{
			printf("Argument : %s\n", argv[i] );
		}
	}
}


