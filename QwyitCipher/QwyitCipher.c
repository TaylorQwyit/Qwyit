#include "QwyitCipher.h"
#include "CipherDef.h"

void ModEncrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	
	uint8_t i = 0;
	for(i; i < LENGTH; i++)
	{
                uint8_t carry = (key1[i] & key2[i] & WORDMASK); 
                result[i] = key1[i] ^ key2[i];
                carry = carry<<1;
                while(carry != 0)
                {
                        uint8_t temp_char = (result[i] & carry & WORDMASK);
                        result[i] = result[i] ^ carry;
                        carry = temp_char << 1;
                }
        }

	#ifdef Cipher_print
        printf("ModEncrypt\n");
        PrintArray(key1, LENGTH);
        PrintArray(key2, LENGTH);
        PrintArray(result, LENGTH);
        #endif
}



void ModDecrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{

        uint8_t i = 0;
        for(i; i < LENGTH; i++)
        {
                uint8_t carry = (~key1[i] & key2[i] & WORDMASK);
                result[i] = key1[i] ^ key2[i];
                carry = carry<<1;
                while(carry != 0)
                {
                        uint8_t temp_char = (~result[i] & carry & WORDMASK);
                        result[i] = result[i] ^ carry;
                        carry = temp_char << 1;
                }
        }

        #ifdef Cipher_print
        printf("ModDecrypt\n");
        PrintArray(key1, LENGTH);
        PrintArray(key2, LENGTH);
        PrintArray(result, LENGTH);
        #endif
}

