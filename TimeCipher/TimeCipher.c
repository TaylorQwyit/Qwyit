#include "../DefineQ.h"
#include "../QwyitCipher/IO.h"
#include "../QwyitCipher/PrimitiveQ.h"
#include "../QwyitCipher/CipherQ.h"

#include "TimeCipher.h"

#include <stdio.h>

Pointer Encrypt(Pointer m, const uint32_t m_len, const uint32_t seed)
{
        Qstate s;
        InitQstate(&s, seed);

	PrintArray(m.p, m_len);
	Pointer cipherText = AllocBytes(m_len*2);

	uint32_t i;
        for(i = 0; i < MESSAGESIZE*8/WORD; i+=1)
        {
                *(cipherText.p+i) = i;
        }


	return cipherText;
	
	
}
