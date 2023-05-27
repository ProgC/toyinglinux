#include <stdio.h>

void func()
{
	for ( int i = 0; i < 10000000UL; i++ )
		;
}

int main(void)
{
	for ( int i = 0; i < 100UL; i++ )
	{
		func();
	}
}

