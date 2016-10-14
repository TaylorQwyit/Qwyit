#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "TimeCipher.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t main(void)
{
        Pointer message = AllocBytes(MESSAGESIZE);

        uint32_t i;
        srand(22);
        for(i = 0; i < MESSAGESIZE*8/WORD; i+=1)
        {
                //*(message.p+i) = 0xff;
                //*(message.p+i) = i;
                *(message.p+i) = ((uint64_t)rand() << 32) | rand();
        }
	
	Pointer ct = Encrypt(message, MESSAGESIZE, rand());

	PrintArray(ct.p, MESSAGESIZE*2);	
}
