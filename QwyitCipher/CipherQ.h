#ifndef CIPHERQ_H_
#define CIPHERQ_H_

typedef struct
{
        void * orA;
        void * orB;
        void * wA;
        void * wB;

        void * EK;
        void * QK;

        void ** OR2;
        void ** OR3;
        void ** W1;
        void ** W2;

        uint16_t index;
        uint32_t iteration;
} Qstate;



void GetNonce(uint8_t * nonce, const uint32_t seed);

void InitQstate(Qstate *s, uint32_t seed);
void NewQstate(Qstate * state);
void CopyQstate(Qstate * state, Qstate * copy);
void FreeQstate(Qstate * state);

void Iteration(Qstate *s);

Pointer MemoryAlloc(const uint32_t charSize);

#endif
