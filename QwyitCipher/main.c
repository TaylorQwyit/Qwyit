//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include "../DefineQ.h"
#include "IO.h"
#include "PrimitiveQ.h"
#include "CipherQ.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{


	unsigned char k1[32] = {0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE, 0x02, 0x46, 0x8A, 0xCE};
	unsigned char k2[32] = {0x02, 0xBF, 0xE4, 0x91, 0xC6, 0x73, 0xA8, 0x55, 0x8A, 0x37, 0x6C, 0x19, 0x4E, 0xFB, 0x20, 0xDD, 0x02, 0xBF, 0xE4, 0x91, 0xC6, 0x73, 0xA8, 0x55, 0x8A, 0x37, 0x6C, 0x19, 0x4E, 0xFB, 0x20, 0xDD};

	unsigned char m1[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

	uint8_t c1[32] = {0};

	uint8_t mask[8] = {0x77, 0x77, 0x77, 0x00, 0x11, 0x77, 0x77, 0x77};
        ModLock(k1, m1, c1, mask);
	
	printf("m1: ");
	PrintCharArray(m1,LENGTH);
	printf("k1: ");
	PrintCharArray(k1,LENGTH);
	printf("c1: ");
	PrintCharArray(c1,LENGTH);


/*
	uint8_t c1[32] = {0};
		
        ModEncrypt(k1, m1, c1);
	
	printf("m1: ");
	PrintCharArray(m1,LENGTH);
	printf("k1: ");
	PrintCharArray(k1,LENGTH);
	printf("c1: ");
	PrintCharArray(c1,LENGTH);
*/	

/*
	uint8_t c1[32] = {0x03, 0x69, 0xcf, 0x25};
	uint8_t c2[32] = {0};
	
        ModEncrypt(k2, c1, c2);
	
	printf("c1: ");
	PrintCharArray(c1,LENGTH);
	printf("k2: ");
	PrintCharArray(k2,LENGTH);
	printf("c2: ");
	PrintCharArray(c2,LENGTH);
*/

/*
	//uint8_t c2[32] = {0x05, 0x18, 0xa3, 0xb6};
	uint8_t c2[32] = {0x01, 0xd6, 0x2b, 0xb4};
	
	uint8_t r1[32] = {0};
	
        ModDecrypt(c2, k1, r1);
	printf("c2: ");
	PrintCharArray(c2,LENGTH);
	printf("k1: ");
	PrintCharArray(k1,LENGTH);
	printf("r1: ");
	PrintCharArray(r1,LENGTH);
*/


/*
	//uint8_t r1[32] = {0x03,0xd2, 0x29,0xf8};

	uint8_t r1[32] = {0x0f, 0x90, 0xa1, 0xf6};
	uint8_t r2[32] = {0};
        ModDecrypt(r1, k2, r2);
	
	printf("r1: ");
	PrintCharArray(r1,LENGTH);
	printf("k2: ");
	PrintCharArray(k2,LENGTH);
	printf("r2: ");
	PrintCharArray(r2,LENGTH);
	printf("m1: ");
	PrintCharArray(m1,LENGTH);
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
*/	
}

