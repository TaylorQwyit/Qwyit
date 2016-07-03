#ifndef CIPHERQ_H_
#define CIPHERQ_H_

typedef struct
{
	Pointer x;

        Pointer orA;
        Pointer orB;
        Pointer wA;
        Pointer wB;

        Pointer EK;
        Pointer QK;

        Pointer * OR2;
        Pointer * OR3;
        Pointer * W1;
        Pointer * W2;

        uint16_t index;
        uint32_t iteration;
} Qstate;



void GetNonce(void * nonce, const uint32_t seed);

void InitQstate(Qstate *s, uint32_t seed);
void NewQstate(Qstate * state);
void CopyQstate(Qstate * state, Qstate * copy);
void FreeQstate(Qstate * state);

void Iteration(Qstate *s);

Pointer MemoryAlloc(const uint32_t charSize);

#endif
