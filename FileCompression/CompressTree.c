#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "CompressTree.h"

#include <stdio.h>

uint8_t * CompressTree(const uint8_t * m, const uint32_t m_len)
{
	PrintCharArray(m, m_len);

	uint32_t messageIndex = 0;
	uint32_t bits = 0;
	for(messageIndex; messageIndex < m_len; messageIndex++)
	{       
		uint8_t mapShift = 0;
		while(mapShift < 8)
		{
			if( (m[messageIndex] >> mapShift & 0x3) == 0)
				bits += 1;
			else if( (m[messageIndex] >> mapShift & 0x3) == 2)
				bits += 2;
			else if( (m[messageIndex] >> mapShift & 0x3) == 1)
				bits += 3;
			else //if(m[messageIndex] & mapMask == 2)
				bits += 3;
			mapShift += 2;
		}
	}

	printf("Size:%d compressed:%d\n", m_len*8, bits);
}
