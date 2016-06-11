#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "CompressTree.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t main(void)
{
	Pointer message;
	message.p  =  MemAlloc(MESSAGESIZE);

	uint32_t i;
	srand(23);
	for(i = 0; i < MESSAGESIZE*8/WORD; i+=1)
	{	
		//*(message.p+i) = 0xff;
		//*(message.p+i) = i;
		*(message.p+i) = ((uint64_t)rand() << 32) | rand();
	}


	printf("Compression:\n");

	PrintArray(message.p, MESSAGESIZE);
	CompressTree(message, MESSAGESIZE);
}
