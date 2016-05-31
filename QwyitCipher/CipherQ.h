#ifndef CIPHERQ_H_
#define CIPHERQ_H_

//typedef struct _Qstate Qstate;

typedef struct
{
        uint8_t * orA;
        uint8_t * orB;
        uint8_t * wA;
        uint8_t * wB;

        uint8_t * EK;
        uint8_t * QK;

        uint8_t ** OR2;
        uint8_t ** OR3;
        uint8_t ** W1;
        uint8_t ** W2;

        uint16_t index;
} Qstate;

void GetNonce(uint8_t * nonce, const uint32_t seed);

void InitQstate(Qstate *s, uint32_t seed);
void NewQstate(Qstate * state);
void CopyQstate(Qstate * state, Qstate * copy);
void FreeQstate(Qstate * state);

void Iteration(Qstate *s);


#endif
