#include "../DefineQ.h"
#include "IO.h"

#include "PrimitiveQ.h"

#include <stdio.h>


/*
	This Method performs a Mod addition of two arrays and places the result into
	the third array result. It works at base Mod of MOD value found in DefineQ.h
	and works at a word size of WORD in bits. It is optimized to run on a 64
	bit processor, but can be easily changed for any sized processor, simply
	change the WORD to corresponding processor size and replace uint64_t with
	the corresponding processor size value.
	
	TODO: make constant time, no timing channel leakage
*/
void ModEncrypt(const void * key1, const void * key2, void * result)
{
	ConstPointer k1,k2;
	Pointer r;

	k1.p = key1;
	k2.p = key2;
	r.p = result;

	Word carry;
	Word temp_carry;
	uint32_t i = 0;
	for(i; i < WORDPERLENGTH ; i++)
	{
                carry.w = *(k1.p+i) & *(k2.p+i) & MODMASK_WORD; 

                *(r.p+i) =  *(k1.p+i) ^ *(k2.p+i);

                carry.w = carry.w << 1;
		
                while(carry.w != 0)
                {
                        temp_carry.w = *(r.p+i) & carry.w & MODMASK_WORD;
			*(r.p+i) = *(r.p+i) ^ carry.w;
                        carry.w = temp_carry.w << 1;
                }
        }

	#ifdef Primitive_p	
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
	
	TODO: make constant time, no timing channel leakage
*/
void ModDecrypt(const void * key1, const void * key2, void * result)
{

        ConstPointer k1,k2;
        Pointer r;

        k1.p = key1;
        k2.p = key2;
        r.p = result;

        Word carry;
        Word temp_carry;

        uint32_t i = 0;
        for(i; i < WORDPERLENGTH ; i++)
        {
                carry.w = ~*(k1.p+i) & *(k2.p+i) & MODMASK_WORD;

                *(r.p+i) =  *(k1.p+i) ^ *(k2.p+i);

                carry.w = carry.w << 1;

                while(carry.w != 0)
                {
                        temp_carry.w = ~*(r.p+i) & carry.w & MODMASK_WORD;
                        *(r.p+i) = *(r.p+i) ^ carry.w;
                        carry.w = temp_carry.w << 1;
                }
        }

	#ifdef Primitive_p	
        printf("ModDecrypt iterations:%d\n", LENGTH/(WORD/8));
        PrintCharArray(key1, LENGTH);
        PrintCharArray(key2, LENGTH);
        PrintCharArray(result, LENGTH);
        #endif
}

/*
Extract works by looping through each 8 bit word in the key, extracting
the MOD value of key and generating an index. The index is then used to
find the corresponding value in alphabet.

TODO: this method works by using byte level addresses. Instead of 
looping through each word, loop based on uint64_t values. Or better yet
use uint64_t values and then mod according to MODMASK. This will result in
the same behavior as the ModEncrypt methods. Allowing for replacement of
uintXX_t with the processor word 
*/
void Extract(const void * k, const void * a, void *r)
{
        #ifdef Primitive_Extract_p
        printf("MOD:%d MODMASK:%x KEYMASK:%d WORDMASK:%d MODPERWORD:%x\n"
        , MOD, MODMASK, KEYMASK, WORDMASK, MODPERWORD);
        #endif
        ConstPointer key,alphabet;
        Pointer result;

        key.p = k;
        alphabet.p = a;
        result.p = r;

        int32_t wordIndex = 0;
        uint32_t index = 0;
        int32_t prevIndex = -1;
        while(wordIndex < WORDPERLENGTH)
        {
           *(result.p+wordIndex) = 0;

           int32_t modIndex = WORD - MOD;
           Word alphabetChar;
           Word resultChar;
           for(modIndex; modIndex >= 0; modIndex -= MOD)
           {
              index = (index +  ((*(key.p+wordIndex)>>modIndex)&MODMASK)) & KEYMASK;
              int32_t bitPosition = index*MOD;
              if(bitPosition>>WORDMASK != prevIndex)
              {
                
                #ifdef Primitive_Extract_p
                printf("New word ");
                #endif
                prevIndex = bitPosition >> WORDMASK;
                alphabetChar.w = *(alphabet.p + prevIndex);
              }
              resultChar.w = (alphabetChar.w >> (~bitPosition&MODPERWORD) )&MODMASK;

              #ifdef Primitive_Extract_p
              printf("index:%d current:%x\n", index, ((*(key.p+wordIndex)>>modIndex)&MODMASK));
              printf("bitPosition:%d 0x%x alphabetChar:%x\n", bitPosition, bitPosition, alphabetChar.w);
              printf("resultChar:%x bitShift:%d\n", resultChar.w,(~bitPosition&MODPERWORD));
              #endif

              *(result.p+wordIndex) |= resultChar.w << modIndex;
              index++;
           }
           wordIndex++;
        }

        #ifdef Primitive_p      
        printf("Extract\n");
        PrintArray(key.p, LENGTH);
        PrintArray(alphabet.p, LENGTH);
        PrintArray(result.p, LENGTH);
        #endif

}



void Combine(const void * key1, const void * key2, void * a1, void * a2, void *result)
{

        
	#ifdef Primitive_p	
	printf("Combine begin\n");
	#endif
        Extract(key1, key2, a1);
        Extract(key2, key1, a2);
        ModEncrypt(a1, a2, result);

	#ifdef Primitive_p	
        printf("Combine\n");
        PrintArray(key1, LENGTH);
        PrintArray(key2, LENGTH);
        PrintArray(result, LENGTH);
        #endif
}

uint32_t Index(const void * alphabet)
{
	
}

void OneWayCut(const uint8_t * key1, const uint8_t * key2, uint8_t * result)
{
	//TODO implement OneWayCut	
}

//TODO FIX, update to use same structure as ModEncrypt, instead of WORDMASK value
void ModLock(const uint8_t * key1, const uint8_t * key2, uint8_t * result,  const uint8_t *mask)
{
	uint32_t i = 0;
	for(i; i < LENGTH; i+=WORD/8)
	{
                uint64_t carry = (*(uint64_t *)((key1+i)) & WORDMASK)
				 & (*(uint64_t *)((key2+i)) & WORDMASK)
                                 //& (uint64_t)MODMASK_WORD; 
				 & (*(uint64_t *)((mask+i)) & WORDMASK);

                *(uint64_t *)(result+i) =  (*(uint64_t *)((key1+i)) & WORDMASK)
					^ (*(uint64_t *)((key2+i)) & WORDMASK);
                carry = carry<<1;
		
                while(carry != 0)
                {
                        uint64_t temp_char = (*(uint64_t *)((result+i)) & WORDMASK)
					     & carry
				 	     & (*(uint64_t *)((mask+i)) & WORDMASK);
					     //& (uint64_t)MODMASK_WORD;

			*(uint64_t *)((result+i)) =  (*(uint64_t *)((result+i)) & WORDMASK)
						     ^ carry;
                        carry = temp_char << 1;
                }
        }
	
	#ifdef Primitive_p	
        printf("ModLock iterations:%d\n", LENGTH/(WORD/8));
	printf("m: ");
        PrintCharArray(mask, LENGTH);
	printf("p: ");
        PrintCharArray(key1, LENGTH);
	printf("k: ");
        PrintCharArray(key2, LENGTH);
	printf("c: ");
        PrintCharArray(result, LENGTH);
        #endif
}
void ModUnlock(const uint8_t * key1, const uint8_t * key2, uint8_t * result,  const uint8_t *mask)
{
        uint32_t i = 0;
        for(i; i < LENGTH; i+=WORD/8)
        {
                uint64_t carry = (~*(uint64_t *)((key1+i)) & WORDMASK)
                                 & (*(uint64_t *)((key2+i)) & WORDMASK)
                                 //& (uint64_t)MODMASK_WORD; 
                                 & (*(uint64_t *)((mask+i)) & WORDMASK);

                *(uint64_t *)(result+i) =  (*(uint64_t *)((key1+i)) & WORDMASK)
                                        ^ (*(uint64_t *)((key2+i)) & WORDMASK);
                carry = carry<<1;

                while(carry != 0)
                {
                        uint64_t temp_char = (~*(uint64_t *)((result+i)) & WORDMASK)
                                             & carry
                                             & (*(uint64_t *)((mask+i)) & WORDMASK);
                                             //& (uint64_t)MODMASK_WORD;

                        *(uint64_t *)((result+i)) =  (*(uint64_t *)((result+i)) & WORDMASK)
                                                     ^ carry;
                        carry = temp_char << 1;
                }
        }

        #ifdef Primitive_p      
        printf("ModUnlock iterations:%d\n", LENGTH/(WORD/8));
        printf("m: ");
        PrintCharArray(mask, LENGTH);
        printf("c: ");
        PrintCharArray(key1, LENGTH);
        printf("k: ");
        PrintCharArray(key2, LENGTH);
        printf("r: ");
        PrintCharArray(result, LENGTH);
        #endif
}
