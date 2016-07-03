#include "../DefineQ.h"
#include "IO.h"
#include "PrimitiveQ.h"
#include "CipherQ.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{


        Pointer k1  =  AllocBytes(LENGTH);
        Pointer k2  =  AllocBytes(LENGTH);
        Pointer r = AllocBytes(LENGTH);
	//r.p = malloc(LENGTH*sizeof(uint8_t) );
	Pointer t = AllocBytes(LENGTH);

        uint32_t i;
        
	Qstate s;
	InitQstate(&s, 0);
	while(i++ < 5)
	{
		Iteration(&s);
		//PrintArray((*s.W1).p, LENGTH);
	}

}

