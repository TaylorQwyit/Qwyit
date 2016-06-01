#include "../DefineQ.h"
#include "IO.h"

#include "PrimativeQ.h"

#include <stdio.h>

/*
	This Method performs a Mod addition of two arrays and places the result into
	the third array result. It works at base Mod of MOD value found in DefineQ.h
	and works at a word size of WORD in bits. It is optimized to run on a 64
	bit processor, but can be easily changed for any sized processor, simply
	change the WORD to corresponding processor size and replace uint64_t with
	the corresponding processor size value.
	
	TODO: The bitwise & using WORDMASK is not necessary if WORD value matches the
	uint64_t value typecast. To optimize further remove WORDMASK and replace uint64_t
	with the matching processor word size (ie uint32_t for a 32 bit processor)
*/
void ModEncrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	uint32_t i = 0;
	for(i; i < LENGTH; i+=WORD/8)
	{
                uint64_t carry = (*(uint64_t *)((key1+i)) & (uint64_t)WORDMASK)
				 & (*(uint64_t *)((key2+i)) & (uint64_t)WORDMASK)
                                 & (uint64_t)MODMASK; 

                *(uint64_t *)(result+i) =  (*(uint64_t *)((key1+i)) & (uint64_t)WORDMASK)
					^ (*(uint64_t *)((key2+i)) & (uint64_t)WORDMASK);
                carry = carry<<1;
		
                while(carry != 0)
                {
                        uint64_t temp_char = (*(uint64_t *)((result+i)) & (uint64_t)WORDMASK)
					     & carry 
					     & (uint64_t)MODMASK;

			*(uint64_t *)((result+i)) =  (*(uint64_t *)((result+i)) & (uint64_t)WORDMASK)
						     ^ carry;
                        carry = temp_char << 1;
                }
        }

	#ifdef Primative_p	
        printf("ModEncrypt\n");
        PrintArray(key1, LENGTH);
        PrintArray(key2, LENGTH);
        PrintArray(result, LENGTH);
        #endif
}



void ModDecrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{

        uint32_t i = 0;
        for(i; i < LENGTH; i++)
        {
                uint8_t carry = (~key1[i] & key2[i] & MODMASK);
                result[i] = key1[i] ^ key2[i];
                carry = carry<<1;
                while(carry != 0)
                {
                        uint8_t temp_char = (~result[i] & carry & MODMASK);
                        result[i] = result[i] ^ carry;
                        carry = temp_char << 1;
                }
        }

	#ifdef Primative_p	
        printf("ModDecrypt\n");
        PrintArray(key1, LENGTH);
        PrintArray(key2, LENGTH);
        PrintArray(result, LENGTH);
        #endif
}


void Extract(const uint8_t * key, const uint8_t * alphabet, uint8_t *result)
{

        uint32_t i;
        uint32_t upperIndex = 0;
        uint32_t lowerIndex = 0;

        for(i = 0; i < LENGTH; i++)
        {

                upperIndex = (lowerIndex + (uint8_t)(key[i]>>4) ) & KEYMASK;

                if((uint32_t)(upperIndex&0x1) == 0)
                {
                        result[i] = alphabet[(uint32_t)(upperIndex>>1)] & 0xF0;
                }
                else
                {
                        result[i] = alphabet[(uint32_t)(upperIndex>>1)] << 4;
                }

                upperIndex++;
                lowerIndex = (upperIndex + (uint8_t)(key[i]&0xF) ) & KEYMASK;
                
                if((uint32_t)(lowerIndex&0x1) != 0)
                {
                        result[i] = result[i] | (alphabet[(uint32_t)(lowerIndex>>1)] & 0xF);
                }
                else
                {

                        result[i] = result[i] | (alphabet[(uint32_t)(lowerIndex>>1)] >> 4);
                }

                lowerIndex++;
        }
	#ifdef Primative_p	
        printf("Extract\n");
        PrintArray(alphabet, LENGTH);
        PrintArray(key, LENGTH);
        PrintArray(result, LENGTH);
        #endif
}

void Combine(const uint8_t * key1, const uint8_t * key2, uint8_t * a1, uint8_t * a2, uint8_t *result)
{

        Extract(key1, key2, a1);
        Extract(key2, key1, a2);
        ModEncrypt(a1, a2, result);

	#ifdef Primative_p	
        printf("Combine\n");
        PrintArray(key1, LENGTH);
        PrintArray(key2, LENGTH);
        PrintArray(result, LENGTH);
        #endif

}

void OneWayCut(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	//TODO implement OneWayCut	
}
