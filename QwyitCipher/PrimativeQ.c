#include "../DefineQ.h"
#include "IO.h"

#include "PrimativeQ.h"

#include <stdio.h>

void ModEncrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{

	const void * K1 = key1;
	const void * K2 = key2;
	const void * r = result;
	
	uint32_t i = 0;
	for(i; i < LENGTH; i++)
	{
                uint64_t carry = ( *(uint8_t *)(K1+i) & *(uint8_t *)(K2+i) & MODMASK); 
                *(uint8_t *)(r+i) =  *(uint8_t *)(K1+i) ^ *(uint8_t *)(K2+i);
                carry = carry<<1;
                while(carry != 0)
                {
                        uint64_t temp_char = (*(uint8_t *)(r+i) & carry & MODMASK);
			*(uint8_t *)(r+i)= *(uint8_t *)(r+i) ^ carry;
                        carry = temp_char << 1;
                }
        }
	/*
	uint32_t i = 0;
	for(i; i < LENGTH; i++)
	{
                uint64_t carry = (key1[i] & key2[i] & MODMASK); 
                result[i] = key1[i] ^ key2[i];
                carry = carry<<1;
                while(carry != 0)
                {
                        uint64_t temp_char = (result[i] & carry & MODMASK);
                        result[i] = result[i] ^ carry;
                        carry = temp_char << 1;
                }
        }
	*/
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
