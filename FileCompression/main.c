#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "CompressTree.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t main(void)
{
	Pointer message = AllocBytes(MESSAGESIZE);

	uint32_t i;
	srand(108);
	for(i = 0; i < MESSAGESIZE*8/WORD; i+=1)
	{	
		//*(message.p+i) = 0xff;
		//*(message.p+i) = i;
		*(message.p+i) = ((uint64_t)rand() << 32) | rand();
	}



	uint32_t minCompress = 0 - 1;
	uint32_t j = 0;
	while(j < 256)
	{
		uint32_t curCompress = CompressTree(message, MESSAGESIZE, j++);
		if( minCompress > curCompress)
		{
			minCompress = curCompress;
			printf("New Low:%d - iteration:%d\n", minCompress, j);
		}
	}

	
	printf("File Size:%d saved:%d\n", MESSAGESIZE*8, MESSAGESIZE*8 - minCompress);
}
