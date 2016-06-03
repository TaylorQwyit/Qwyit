//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include "../DefineQ.h"
#include "IO.h"
#include "PrimativeQ.h"
#include "CipherQ.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{

	printf("QwyitCipher: main\n");

/*
	uint8_t * k1  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
	uint8_t * k2  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
	uint8_t * result  =  (void *)malloc(sizeof(uint8_t)*LENGTH);

	uint32_t i = 0;
	for(i; i< LENGTH; i++)
	{
		
		k1[i] = i+129*3;
	}
	
	uint8_t EK[64] = {  0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

	//uint64_t EK[1] = { 0x0123456789ABCDEF };
	Extract(k1, EK, result);	
	//ModDecrypt(result, EK, k2);	

*/

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
	
	
        ModEncrypt(EK, OR, R);
        Combine(QK, R, a1, a2, A);
        Extract(QK, A, W);
        ModEncrypt(W, message, encrypted);
        ModDecrypt(encrypted, W, decrypted);
	
	printf("Cipher Test\n");
	printf("W(%d)\n", memcmp(R, rTest, LENGTH));
	PrintCharArray(R, LENGTH);
	PrintCharArray(rTest, LENGTH);
	printf("R(%d)\n", memcmp(W, wTest, LENGTH));
	PrintCharArray(W, LENGTH);
	PrintCharArray(wTest, LENGTH);
	
	printf("Decrypted Message(%d)\n", memcmp(decrypted, message, LENGTH));

}

