#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "CompressTree.h"

#include <stdio.h>

uint32_t CompressTree(Pointer m, const uint32_t m_len, const uint32_t seed)
{
	
	Qstate s;	
	InitQstate(&s, seed);
		
	uint32_t bits = 0;
	uint32_t bits2 = 0;
	uint32_t i = 0;
	for(i; i < m_len*8/WORD; i++)
	{ 
		
		Iteration(&s);
		uint32_t treeVal = *(*s.W1);
		uint32_t j = 0;	
		for(j; j < WORD; j+= TREE)
		{
			uint32_t x = *(m.p+i) & (TREEMASK << j);
			
			#ifdef CompressTree_p
			printf("message:%x\n", x );
			#endif	
			uint32_t bitsAdded = 0;
			while( x != ((treeVal ^ (bitsAdded++<<j) ) & (TREEMASK << j)) )
			{
				
				#ifdef CompressTree_p
				printf("m:%x treeVal:%x\n", x, treeVal ^ (bitsAdded<<j));
				#endif	
			}
			#ifdef CompressTree_p
			printf("found:%x=%x with bits=%d\n", x, treeVal ^ (bitsAdded<<j), bitsAdded);
			#endif	
			
			if(bitsAdded <= (1 << (TREE -1)) / 2)
				bits2 += TREE -1;
			else if (bitsAdded <= (1 << (TREE-1)))
				bits2 += TREE;
			else
				bits2 += TREE + 1;
		

		}
	}
	#ifdef CompressTree_p
	PrintArray(m.p, m_len);
	printf("Tree:%d TreeMask:%x\n",TREE, TREEMASK);
	printf("Size:%d compressed:%d, %d\n", m_len*8, bits, bits2);
	#endif
	FreeQstate(&s);
	return bits2;
}
