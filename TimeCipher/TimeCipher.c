#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "TimeCipher.h"

#include <stdio.h>

Pointer Encrypt(Pointer m, const uint32_t m_len, const uint32_t seed)
{
        Qstate s;
        InitQstate(&s, 10);

	PrintArray(m.p, m_len);
	Pointer cipherText = AllocBytes(m_len*2);


        uint32_t i = 0;
        for(i; i < m_len*8/WORD; i++)
        {
		
                *(cipherText.p+i) = i;
                
		Iteration(&s);
                Pointer tv = *s.W1;
                uint64_t treeVal = *(tv.p);
                uint64_t j = 0;
                for(j; j < WORD; j+= TREE)
                {
		
		}
	}

	return cipherText;
	
	
}
