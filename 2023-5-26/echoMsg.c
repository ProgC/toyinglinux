#include <stdio.h>
#include <string.h>

/* one library function call another library function  */
int echoMsg(char *msg)
{
	int echoMsg2(char *msg);

	printf("The library function echoMsg() was called\n");
	return echoMsg2(msg);
}

/* echoMsg2 */
int echoMsg2(char *msg)
{
	int len = 0;
	printf("The library function echoMsg2() was called\n");
	if ( msg != NULL ) {
		len = strlen(msg);
		printf("*** Your message is: %s\n", msg);
	}
	return len;
}


	
