#include "../DefineQ.h"
#include "IO.h"
#include "PrimitiveQ.h"
#include "CipherQ.h"

#include <stdio.h>
#include <stdlib.h>

void extract(const void * k, const void * a, void *r)
{
        #ifdef Primitive_Extract_p
        printf("MOD:%d MODMASK:%x KEYMASK:%d WORDMASK:%d MPB:%x\n"
	, MOD, MODMASK, KEYMASK, WORDMASK, MPB);
        #endif

        ConstPointer key,alphabet;
        Pointer result;

        key.p = k;
        alphabet.p = a;
        result.p = r;



        int32_t wordIndex = 0;
        uint32_t index = 0;
        while(wordIndex < WORDPERLENGTH)
        {
           *(result.p+wordIndex) = 0;

           int32_t modIndex = WORD - MOD;
	   int32_t prevIndex = -1;
	   Word alphabetChar;
	   Word resultChar;
           for(modIndex; modIndex >= 0; modIndex -= MOD)
           {
              index = (index +  ((*(key.p+wordIndex)>>modIndex)&MODMASK)) & KEYMASK;
              int32_t bitPosition = index*MOD;
	      if(bitPosition>>WORDMASK != prevIndex)
	      {
		
                #ifdef Primitive_Extract_p
		printf("NEW word ");
                #endif
		prevIndex = bitPosition >> WORDMASK;
		alphabetChar.w = *(alphabet.p + (bitPosition>>prevIndex));
	      }
              resultChar.w = (alphabetChar.w >> (~bitPosition&MPB) )&MODMASK;

              #ifdef Primitive_Extract_p
              printf("index:%d current:%x\n", index, ((*(key.p+wordIndex)>>modIndex)&MODMASK));
              printf("bitPosition:%d 0x%x alphabetChar:%x\n", bitPosition, bitPosition, alphabetChar.w);
              printf("resultChar:%x bitShift:%d\n", resultChar.w,(~bitPosition&MPB));
              #endif

              *(result.p+wordIndex) |= resultChar.w << modIndex;
              index++;
           }
           wordIndex++;
        }

	#ifdef Primitive_p      
        printf("New Extract\n");
        PrintArray(key.p, LENGTH);
        PrintArray(alphabet.p, LENGTH);
        PrintArray(result.p, LENGTH);
        #endif

}

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

	extract(k1.p, k2.p, r.p);
	uint8_t t1[8] = { 0x3d, 0xfa, 0xc8, 0x9e, 0x47, 0x69, 0x2c, 0xde };
	uint8_t t2[8] = { 0x43, 0x6d, 0x78, 0x55, 0x33, 0xea, 0x88, 0xfb };
	uint8_t tr[8];

	Extract(t1, t2, tr);	
/*
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
        Combine(QK, R.p, a1.p, a2.p, A.p);
        Extract(QK, A.p, W.p);
        ModEncrypt(W.p, message, encrypted.p);
        ModDecrypt(encrypted.p, W.p, decrypted.p);

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

