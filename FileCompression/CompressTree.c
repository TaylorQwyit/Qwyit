#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "CompressTree.h"

#include <stdio.h>

uint8_t * CompressTree(Pointer m, const uint32_t m_len)
{
	PrintArray(m.p, m_len);

	Qstate s;	
	InitQstate(&s, 0);
	
	uint32_t bits = 0;
	uint32_t i = 0;
	for(i; i < m_len*8/WORD; i++)
	{ 
		uint8_t mapShift = 0;
		Iteration(&s);
		while(mapShift < 8)
		{
			if( (*(m.p+i) >> mapShift & 0x3) == 0)
				bits += 1;
			else if( (*(m.p+i)  >> mapShift & 0x3) == 2)
				bits += 2;
			else if( (*(m.p+i)  >> mapShift & 0x3) == 1)
				bits += 3;
			else //if(m[i] & mapMask == 2)
				bits += 3;
			mapShift += 2;
		}
	}

	printf("Size:%d compressed:%d\n", m_len*8, bits);

}
