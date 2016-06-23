#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "CompressTree.h"

#include <stdio.h>

uint8_t * CompressTree(Pointer m, const uint32_t m_len)
{
	PrintArray(m.p, m_len);
	printf("Tree:%d TreeMask:%x\n",TREE, TREEMASK);
	Qstate s;	
	InitQstate(&s, 0);
	
	uint32_t bits = 0;
	uint32_t bits2 = 0;
	uint32_t i = 0;
	for(i; i < m_len*8/WORD; i++)
	{ 
		
		Iteration(&s);
		uint32_t treeVal = 0;
		uint32_t j = 0;	
		for(j; j < WORD; j+= TREE)
		{
			uint32_t x = *(m.p+i) & (TREEMASK << j);
			printf("message:%x\n", x );
			
			uint32_t bitsAdded = 0;
			while( x != (treeVal ^ (bitsAdded++<<j) ) )
			{
				printf("m:%x treeVal:%x\n", x, treeVal ^ (bitsAdded<<j));
			}
			printf("found:%x=%x with bits=%d\n", x, treeVal ^ (bitsAdded<<j), bitsAdded);
			if(bitsAdded == 4)
				bits2 += 3;
			else
				bits2 += bitsAdded;
		}
		
		uint8_t mapShift = 0;
		while(mapShift < 8)
		{
			if( (*(m.p+i) >> mapShift & 0x3) == 0)
				bits += 1;
			else if( (*(m.p+i)  >> mapShift & 0x3) == 1)
				bits += 2;
			else if( (*(m.p+i)  >> mapShift & 0x3) == 2)
				bits += 3;
			else //if(m[i] & mapMask == 2)
				bits += 3;
			mapShift += 2;
		}
	}

	printf("Size:%d compressed:%d, %d\n", m_len*8, bits, bits2);

}
