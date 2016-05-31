#ifndef CIPHERQ_H_
#define CIPHERQ_H_

typedef struct _Qstate Qstate;
/*
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
}Qstate;
*/
void GetNonce(uint8_t * nonce, const uint32_t seed);

extern void InitQstate(struct Qstate *s, uint32_t seed);
extern void NewQstate(struct Qstate * state);
extern void CopyQstate(struct Qstate * state, Qstate * copy);
extern void FreeQstate(struct Qstate * state);

extern void Iteration(struct Qstate *s);


#endif
