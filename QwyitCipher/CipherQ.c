#include "../DefineQ.h"
#include "IO.h"
#include "PrimitiveQ.h"

#include "CipherQ.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Pointer MemoryAlloc(const uint32_t charSize)
{
	Pointer memPointer;
	#if (WORD == 64)
	memPointer.p = (uint64_t *)malloc(sizeof(uint8_t)*LENGTH);
	#elif (WORD == 32)
	memPointer.p = (uint32_t *)malloc(sizeof(uint8_t)*LENGTH);
	#elif (WORD == 16)
	memPointer.p = (uint16_t *)malloc(sizeof(uint8_t)*LENGTH);
	#elif (WORD == 8)
	memPointer.p = (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
	#endif
	return memPointer;
}
*/

void GetNonce(void * n, const uint32_t seed)
{

	uint8_t * nonce = n;
        uint32_t i;
	srand(seed);
        for(i = 0;i<LENGTH;i+=1)
        {
                nonce[i] = rand() % 256;
        }
}

void InitOR(void * or, const uint32_t value)
{

	uint8_t * OR = or;
       	uint32_t i;
        for(i = 0;i<LENGTH;i+=1)
        {
                OR[i] = (value >> (8*i) ) & 0xFF;
        }

}
void Round(void * EK, void * QK, void * OR, void * Next_W,  void * Next_OR)
{
	
       	Pointer A = AllocBytes(LENGTH); 
       	Pointer R = AllocBytes(LENGTH); 
       	Pointer a1 = AllocBytes(LENGTH); 
       	Pointer a2 = AllocBytes(LENGTH); 

	#ifdef Round_p
        printf("Round      OR:");
        PrintCharArray(OR, LENGTH);
	#endif


	ModEncrypt(EK, OR, R.p);
        Combine(QK, R.p, a1.p, a2.p, A.p);
        Extract(QK, A.p, Next_W);
	ModEncrypt(Next_W, R.p, Next_OR);

	ModEncrypt(QK, OR, QK);
	ModEncrypt(EK, Next_OR, EK);
	
	#ifdef Round_p
        printf(" round NextOR:");
        PrintCharArray(Next_OR, LENGTH);
        printf(" round      W:");
        PrintCharArray(Next_W, LENGTH);
	#endif

	free(A.p);
	free(R.p);
	free(a1.p);
	free(a2.p);
}

void InitQstate(Qstate *s, uint32_t seed)
{
	//s->x = AllocBytes(LENGTH);
        s->orA  = AllocBytes(LENGTH);// (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->orB  = AllocBytes(LENGTH);// (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->wA  =  AllocBytes(LENGTH);//(uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->wB  =  AllocBytes(LENGTH);//(uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        
	s->EK  = AllocBytes(LENGTH);//(uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->QK  = AllocBytes(LENGTH); //(uint8_t *)malloc(sizeof(uint8_t)*LENGTH);

	GetNonce(s->EK.p, 23);
	GetNonce(s->QK.p, 108);
	InitOR(s->orB.p, seed);
	#ifdef Iteration_p
	printf("Init:\n");
	printf("EK: ");
	PrintArray(s->EK.p, LENGTH);
	printf("QK: ");
	PrintArray(s->QK.p, LENGTH);
	printf("OR:");
	PrintArray(s->orB.p, LENGTH);
	#endif

	Round(s->EK.p, s->QK.p, s->orB.p, s->wA.p, s->orA.p);
	Round(s->EK.p, s->QK.p, s->orA.p, s->wB.p, s->orB.p);

	s->OR2 = &(s->orA);
	s->OR3 = &(s->orB);	
	s->W1 = &(s->wA);	
	s->W2 = &(s->wB);

	s->index = 0;	
	s->iteration = 0;	
}

/*
void NewQstate(Qstate * state)
{
	state->orA  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        state->orB  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        state->wA  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        state->wB  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        
	state->EK  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        state->QK  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
	
	state->index = 0;
	state->iteration = 0;
}

void CopyQstate(Qstate * state, Qstate * copy)
{
	memcpy(state->orA, *copy->OR2, LENGTH);
	memcpy(state->orB, *copy->OR3, LENGTH);
	memcpy(state->wA, *copy->W1, LENGTH);
	memcpy(state->wB, *copy->W2, LENGTH);
	memcpy(state->EK, copy->EK, LENGTH);
	memcpy(state->QK, copy->QK, LENGTH);
	
	state->OR2 = &(state->orA);
	state->OR3 = &(state->orB);	
	state->W1 = &(state->wA);	
	state->W2 = &(state->wB);
	state->index = copy->index;
}
*/
void FreeQstate(Qstate * state)
{
        free(state->orA.p);
        free(state->orB.p);
        free(state->wA.p);
        free(state->wB.p);
        free(state->EK.p);
        free(state->QK.p);
}

void Iteration(Qstate *s)
{
	Pointer tempW = *s->W1;
	*s->W1 = *s->W2;
	*s->W2 = tempW;
	
	Round(s->EK.p, s->QK.p, (*s->OR3).p, (*s->W2).p, (*s->OR2).p);

	Pointer tempOR = *s->OR2;
	*s->OR2 = *s->OR3;
	*s->OR3 = tempOR;
	
	s->index = s->index - LENGTH;
	s->iteration++;
	
	#ifdef Iteration_p
	printf("Iteration:%d\n", s->iteration);
	printf("W1: ");
	PrintArray(  (*s->W1).p, LENGTH);
	printf("W2: ");
	PrintArray(  (*s->W2).p, LENGTH);
	printf("OR2:");
	PrintArray( (*s->OR2).p, LENGTH);
	printf("OR3:");
	PrintArray(  (*s->OR3).p, LENGTH);
	#endif
}
