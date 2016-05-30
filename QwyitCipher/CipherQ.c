#include "PrimativeQ.h"
#include "DefineQ.h"
#include "CipherQ.h"
#include "IO.h"

void GetNonce(uint8_t * nonce, const uint32_t seed)
{

        uint32_t i;
	srand(seed);
        for(i = 0;i<LENGTH;i+=1)
        {
                nonce[i] = rand() % 256;
        }
}

void Round(uint8_t * EK, uint8_t * QK, uint8_t * OR, uint8_t * Next_W,  uint8_t * Next_OR)
{
	
        uint8_t * A  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        uint8_t * R  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        uint8_t * a1  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        uint8_t * a2  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);

	#ifdef wround_p
        printf("Round\nor:");
        PrintArray(OR, LENGTH);
	#endif


	ModEncrypt(EK, OR, R);
        Combine(QK, R, a1, a2, A);
        Extract(QK, A, Next_W);
	ModEncrypt(Next_W, R, Next_OR);

	//ModEncrypt(QK, OR, QK);
	//ModEncrypt(EK, OR, EK);
	
	#ifdef wround_p
        printf("next_or:");
        PrintArray(Next_OR, LENGTH);
        printf("w:");
        PrintArray(Next_W, LENGTH);
	#endif

	free(A);
	free(R);
	free(a1);
	free(a2);
}
