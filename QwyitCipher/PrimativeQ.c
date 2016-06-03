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
	
	TODO: make constant time, no timing channel leakage
*/
void ModEncrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	uint32_t i = 0;
	for(i; i < LENGTH; i+=WORD/8)
	{
                uint64_t carry = (*(uint64_t *)((key1+i)) & WORDMASK)
				 & (*(uint64_t *)((key2+i)) & WORDMASK)
                                 & (uint64_t)MODMASK_WORD; 

                *(uint64_t *)(result+i) =  (*(uint64_t *)((key1+i)) & WORDMASK)
					^ (*(uint64_t *)((key2+i)) & WORDMASK);
                carry = carry<<1;
		
                while(carry != 0)
                {
                        uint64_t temp_char = (*(uint64_t *)((result+i)) & WORDMASK)
					     & carry 
					     & (uint64_t)MODMASK_WORD;

			*(uint64_t *)((result+i)) =  (*(uint64_t *)((result+i)) & WORDMASK)
						     ^ carry;
                        carry = temp_char << 1;
                }
        }
	
	#ifdef Primative_p	
        printf("ModEncrypt iterations:%d\n", LENGTH/(WORD/8));
        PrintCharArray(key1, LENGTH);
        PrintCharArray(key2, LENGTH);
        PrintCharArray(result, LENGTH);
        #endif
}

/*
	This Method performs a Mod subtraction of key2 from key1 and places the result into
	the third array result. It works at base Mod of MOD value found in DefineQ.h
	and works at a word size of WORD in bits. It is optimized to run on a 64
	bit processor, but can be easily changed for any sized processor, simply
	change the WORD to corresponding processor size and replace uint64_t with
	the corresponding processor size value.
	
	TODO: The bitwise & using WORDMASK is not necessary if WORD value matches the
	uint64_t value typecast. To optimize further remove WORDMASK and replace uint64_t
	with the matching processor word size (ie uint32_t for a 32 bit processor)

	TODO: make constant time, no timing channel leakage
*/
void ModDecrypt(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	uint32_t i = 0;
	for(i; i < LENGTH; i+=WORD/8)
	{
                uint64_t carry = (~*(uint64_t *)((key1+i)) & WORDMASK)
				 & (*(uint64_t *)((key2+i)) & WORDMASK)
                                 & (uint64_t)MODMASK_WORD; 

                *(uint64_t *)(result+i) =  (*(uint64_t *)((key1+i)) & WORDMASK)
					^ (*(uint64_t *)((key2+i)) & WORDMASK);
                carry = carry<<1;
		
                while(carry != 0)
                {
                        uint64_t temp_char = (~*(uint64_t *)((result+i)) & WORDMASK)
					     & carry 
					     & (uint64_t)MODMASK_WORD;

			*(uint64_t *)((result+i)) =  (*(uint64_t *)((result+i)) & WORDMASK)
						     ^ carry;
                        carry = temp_char << 1;
                }
        }

	#ifdef Primative_p	
        printf("ModDecrypt iterations:%d\n", LENGTH/(WORD/8));
        PrintCharArray(key1, LENGTH);
        PrintCharArray(key2, LENGTH);
        PrintCharArray(result, LENGTH);
        #endif
}


void Extract(const uint8_t * key, const uint8_t * alphabet, uint8_t *result)
{

	if(BIGENDIAN)
		printf("Big Endian\n");
	else
		printf("Little Endian\n");


        PrintCharArray(key, LENGTH);
        PrintCharArray(alphabet, LENGTH);
	printf("MOD:%d MODMASK:%x MODPERBYTE:%d\n", MOD, MODMASK, MODPERBYTE);
        int32_t wordIndex = 0;
	uint32_t index = 0;
	while(wordIndex < LENGTH)
	{
	   int32_t modIndex = 8 - MOD;
	   for(modIndex; modIndex >= 0; modIndex -= MOD)
	   {
	      index = (index +  ((*(key+wordIndex)>>modIndex)&MODMASK)) & KEYMASK;
	      printf("index:%d current:%x\n", index, ((*(key+wordIndex)>>modIndex)&MODMASK));
	      uint32_t bitPosition = index*MOD;
	      uint8_t alphabetChar = *(alphabet + (bitPosition>>3));
	      printf("bitPosition:%d 0x%x alphabetChar:%x\n", bitPosition, bitPosition, alphabetChar);
	      uint8_t resultChar = (alphabetChar >> (~bitPosition&MOD) )&MODMASK;
	      printf("resultChar:%x bitShift:%x\n", resultChar,(~bitPosition&MOD));

	      uint64_t resultArray = *(uint64_t *)alphabet;
	      //SHIFT is required here because of little endian machine,
	      //need to investiage to make sure no shifting required for big endian
	      int8_t shift = ( (index&1) == 0) ? 4 : -4;
	      uint64_t r = (resultArray >> MOD*index + shift)&MODMASK;
	      printf("a:%lx index%d: shift:%d bitposition:%d\n", resultArray,index,shift, MOD*index+shift); 
	      printf("result pre-update:%x\n", *(result+wordIndex));
	      *(result+wordIndex) |= r<< modIndex;
	      printf("result:%x shifted<-%d current value:%lx\n\n", *(result+wordIndex),modIndex, r);
	      
	      index++;
	   }
	   wordIndex++;
	}


/*
	uint32_t i;
	uint32_t upperIndex = 0;
        for(i = 0; i < LENGTH*2*MOD; i+=MOD)
        {
                //printf("iteration:%d\n", i);
		upperIndex = (upperIndex + (uint8_t)(   (*(key+i/8) >> (4&~i))&0xF) ) & KEYMASK;
		printf("index:%d\n", upperIndex);

		if((uint32_t)(upperIndex&0x1) == 0)
                {
			//printf("result:%x\n", alphabet[(uint32_t)(upperIndex>>1)] & 0xF0);
                        result[i/8] |= (alphabet[(uint32_t)(upperIndex>>1)] & 0xF0)>>(4&i) ;
                }
                else
                {
			//printf("result:%x\n", alphabet[(uint32_t)(upperIndex>>1)] << 4 );
                        result[i/8] |= (alphabet[(uint32_t)(upperIndex>>1)] << 4 )>>(4&i) ;
                }

                upperIndex++;
	}
*/
	/*
	uint32_t i;
	uint32_t upperIndex = 0;
	uint32_t lowerIndex = 0;

        for(i = 0; i < LENGTH; i++)
        {

                upperIndex = (lowerIndex + (uint8_t)(key[i]>>4) ) & KEYMASK;
		
		printf("index upper:%d\n", upperIndex);
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
                
		printf("index lower:%d\n", lowerIndex);
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
	*/

	#ifdef Primative_p	
        printf("Extract\n");
        PrintCharArray(key, LENGTH);
        PrintCharArray(alphabet, LENGTH);
        PrintCharArray(result, LENGTH);
        #endif
}

void Combine(const uint8_t * key1, const uint8_t * key2, uint8_t * a1, uint8_t * a2, uint8_t *result)
{

        Extract(key1, key2, a1);
        Extract(key2, key1, a2);
        ModEncrypt(a1, a2, result);

	#ifdef Primative_p	
        printf("Combine\n");
        PrintCharArray(key1, LENGTH);
        PrintCharArray(key2, LENGTH);
        PrintCharArray(result, LENGTH);
        #endif

}

void OneWayCut(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	//TODO implement OneWayCut	
}
