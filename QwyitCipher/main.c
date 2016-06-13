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
        Pointer r  =  AllocBytes(LENGTH);

        uint32_t i;
        srand(23);
        for(i = 0; i < MESSAGESIZE*8/WORD; i+=1)
        {
                *(k1.p+i) = ((uint64_t)rand() << 32) | rand();
                *(k2.p+i) = ((uint64_t)rand() << 32) | rand();
        }

	ModEncrypt(k1.p, k2.p, r.p);	


	Pointer R = AllocBytes(LENGTH);
	Pointer W = AllocBytes(LENGTH);
	Pointer A = AllocBytes(LENGTH);
	Pointer a1 = AllocBytes(LENGTH);
	Pointer a2 = AllocBytes(LENGTH);
	Pointer encrypted = AllocBytes(LENGTH);
	Pointer decrypted = AllocBytes(LENGTH);

	unsigned char message[32] = "This is a test of a Qwyit Cipher";
	
	unsigned char EK[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	unsigned char QK[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

	unsigned char OR[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};


	unsigned char rTest[32] = {0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE};
	unsigned char wTest[32] = {0x02, 0xBF, 0xE4, 0x91, 0xC6, 0x73, 0xA8, 0x55, 0x8A, 0x37, 0x6C, 0x19, 0x4E, 0xFB, 0x20, 0xDD, 0x02, 0xBF, 0xE4, 0x91, 0xC6, 0x73, 0xA8, 0x55, 0x8A, 0x37, 0x6C, 0x19, 0x4E, 0xFB, 0x20, 0xDD};

        ModEncrypt(EK, OR, R.p);
        //Combine(QK, R.p, a1.p, a2.p, A.p);
        //Extract(QK, A.p, W.p);
        ModEncrypt(R.p, message, encrypted.p);
        ModDecrypt(encrypted.p, R.p, decrypted.p);
/*
	printf("Cipher Test\n");
	printf("W(%d)\n", memcmp(R.p, rTest, LENGTH));
	PrintCharArray(R.p, LENGTH);
	PrintCharArray(rTest, LENGTH);
	printf("R(%d)\n", memcmp(W.p, wTest, LENGTH));
	PrintCharArray(W.p, LENGTH);
	PrintCharArray(wTest, LENGTH);
	
	printf("Decrypted Message(%d)\n", memcmp(decrypted, message, LENGTH));
*/
/*
	printf("QwyitCipher: main\n");
	Qstate state;
	InitQstate(&state, 0);
	
	uint32_t i = 0;
	for(i;i<100;i++)
	{
		Iteration(&state);
		PrintCharArray(*state.W1, LENGTH);
	}
*/

	/*	
	unsigned char * R  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char * W  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char * A  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char * a1  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char * a2  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char * encrypted  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char * decrypted  =  (unsigned char *)malloc(sizeof(char)*LENGTH);
	unsigned char message[32] = "This is a test of a Qwyit Cipher";
	
	unsigned char EK[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	unsigned char QK[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

	unsigned char OR[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};


	unsigned char rTest[32] = {0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE};
	unsigned char wTest[32] = {0x02, 0xBF, 0xE4, 0x91, 0xC6, 0x73, 0xA8, 0x55, 0x8A, 0x37, 0x6C, 0x19, 0x4E, 0xFB, 0x20, 0xDD, 0x02, 0xBF, 0xE4, 0x91, 0xC6, 0x73, 0xA8, 0x55, 0x8A, 0x37, 0x6C, 0x19, 0x4E, 0xFB, 0x20, 0xDD};
	
	
       // ModEncrypt(EK, OR, r.p);
        //Combine(QK, R, a1, a2, A);
        //Extract(QK, A, W);
        //ModEncrypt(W, message, encrypted);
        //ModDecrypt(encrypted, W, decrypted);
	
	printf("Cipher Test\n");
	printf("W(%d)\n", memcmp(R, rTest, LENGTH));
	PrintCharArray(R, LENGTH);
	PrintCharArray(rTest, LENGTH);
	printf("R(%d)\n", memcmp(W, wTest, LENGTH));
	PrintCharArray(W, LENGTH);
	PrintCharArray(wTest, LENGTH);
	
	printf("Decrypted Message(%d)\n", memcmp(decrypted, message, LENGTH));
	*/

}

