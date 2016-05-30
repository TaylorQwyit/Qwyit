#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../QwyitCipher/IO.h"
#include "../DefineQ.h"

#include "CompressTree.h"

uint32_t main(void)
{
	uint8_t * message  =  (uint8_t *)malloc(sizeof(uint8_t)*MESSAGESIZE);

	uint32_t i;
	srand(23);
	for(i = 0; i < MESSAGESIZE; i+=1)
	{	
		//message[i] = 0x11;
		//message[i] = i;
		message[i] = rand() % 256;
	}


	printf("Compression:\n");
	CompressTree(message, MESSAGESIZE);
}
