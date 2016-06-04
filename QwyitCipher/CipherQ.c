

#include "../DefineQ.h"
#include "IO.h"
#include "PrimitiveQ.h"

#include "CipherQ.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void GetNonce(uint8_t * nonce, const uint32_t seed)
{

        uint32_t i;
	srand(seed);
        for(i = 0;i<LENGTH;i+=1)
        {
                nonce[i] = rand() % 256;
        }
}

void Round(uint8_t * EK, uint8_t * QK, uint8_t * OR, uint8_t * Next_W,  uint8_t * Next_OR)
{
	
        uint8_t * A  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        uint8_t * R  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        uint8_t * a1  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        uint8_t * a2  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);

	#ifdef Round_p
        printf("Round      OR:");
        PrintCharArray(OR, LENGTH);
	#endif


	ModEncrypt(EK, OR, R);
        Combine(QK, R, a1, a2, A);
        Extract(QK, A, Next_W);
	ModEncrypt(Next_W, R, Next_OR);

	//ModEncrypt(QK, OR, QK);
	//ModEncrypt(EK, OR, EK);
	
	#ifdef Round_p
        printf(" round NextOR:");
        PrintCharArray(Next_OR, LENGTH);
        printf(" round      W:");
        PrintCharArray(Next_W, LENGTH);
	#endif

	free(A);
	free(R);
	free(a1);
	free(a2);
}

void InitQstate(Qstate *s, uint32_t seed)
{
        s->orA  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->orB  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->wA  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->wB  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        
	s->EK  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);
        s->QK  =  (uint8_t *)malloc(sizeof(uint8_t)*LENGTH);

	GetNonce(s->EK, 23);
	GetNonce(s->QK, 108);
	GetNonce(s->orB, seed);

	Round(s->EK, s->QK, s->orB, s->wA, s->orA);
	Round(s->EK, s->QK, s->orA, s->wB, s->orB);

	s->OR2 = &(s->orA);
	s->OR3 = &(s->orB);	
	s->W1 = &(s->wA);	
	s->W2 = &(s->wB);
	s->index = 0;	
	s->iteration = 0;	
}


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


void Iteration(Qstate *s)
{
	uint8_t * tempW = *s->W1;
	*s->W1 = *s->W2;
	*s->W2 = tempW;
	
	Round(s->EK, s->QK, *s->OR3, *s->W2, *s->OR2);

	uint8_t * tempOR = *s->OR2;
	*s->OR2 = *s->OR3;
	*s->OR3 = tempOR;
	
	s->index = s->index - LENGTH;
	s->iteration++;
	
	#ifdef Iteration_p
	printf("Iteration:%d\n", s->iteration);
	printf("W1: ");
	PrintCharArray(* s->W1, LENGTH);
	printf("W2: ");
	PrintCharArray(* s->W2, LENGTH);
	printf("OR2:");
	PrintCharArray(* s->OR2, LENGTH);
	printf("OR3:");
	PrintCharArray(* s->OR3, LENGTH);
	#endif
}
