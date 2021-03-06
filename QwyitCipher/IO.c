
#include "../DefineQ.h"
#include "IO.h"

#include <stdio.h>

void PrintCharArray(const uint8_t * array, const uint32_t length)
{
        uint32_t i;
        for(i = 0; i < length; i++)
        {
                printf("%02x",array[i]);

        }
        printf("\n");
}

void PrintArray(const void * array, const uint32_t length)
{
        uint32_t i;
	ConstPointer a;
	a.p = array;
	//printf("length:%d WORD%d loop:%d\n", length, WORD, length/WORD);
        for(i = 0; i < length*8/WORD; i++)
        {
		#if (WORD == 64)
		printf("%016lx",*(a.p+i));
		#elif (WORD == 32)
		printf("%08x",*(a.p+i));
		#elif (WORD == 16)
		printf("%04x",*(a.p+i));
		#elif (WORD == 8)
		printf("%02x",*(a.p+i));
		#endif
        }
        printf("\n");
}
