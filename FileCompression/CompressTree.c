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
		Pointer tv = *s.W1;
		uint64_t treeVal = *(tv.p);
		uint64_t j = 0;	
		for(j; j < WORD; j+= TREE)
		{
			//uint64_t x = *(m.p+i) & (TREEMASK << j);
			//uint64_t x = *(m.p+i) & 0xFFFFFFFF;
			
			#ifdef CompressTree_p
			printf("m:%x q:%lx\n", *(m.p+i) , treeVal);
			#endif	
			uint64_t bitsAdded = ((*(m.p+i) ^ treeVal) >> j ) & 0xFFFFFFFF;
			//while( x != (treeVal ^ (bitsAdded<<j) ) & 0xFFFFFFFF )
			//TODO fix the while loop to use subtraction instead
			//while( x != ((treeVal ^ (bitsAdded<<j) ) & (TREEMASK << j)) )
			{
				//bitsAdded++;
				#ifdef CompressTree_p
				//printf("m:%x treeVal:%x\n", x, treeVal ^ (bitsAdded<<j));
				#endif	
			}
			#ifdef CompressTree_p
			printf("found:%x=%lx w/ bits=%ld\n",*(m.p+i), treeVal, bitsAdded);
			#endif	
			Word limit;
			limit.w = (1 << (TREE-1));
				
			if(bitsAdded < limit.w / 2)
			{
				#ifdef CompressTree_p
                        	printf("bits:%ld<%u, +%d\n", bitsAdded, limit.w/2, TREE-1);
                        	#endif
				bits2 += TREE -1;
			}
			else if (bitsAdded < limit.w)
			{
				#ifdef CompressTree_p
                        	printf("bits:%ld<%u, +%d\n", bitsAdded, limit.w, TREE);
                        	#endif
				bits2 += TREE;
			}
			else
			{	
				#ifdef CompressTree_p
                        	printf("bits:%ld>%u, +%d\n", bitsAdded, limit.w, TREE+1);
                        	#endif
				bits2 += TREE + 1;
			}

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
