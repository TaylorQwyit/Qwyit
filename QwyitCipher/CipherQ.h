#ifndef CIPHERQ_H_
#define CIPHERQ_H_

#include "DefineQ.h"
#include "PrimativeQ.h"
#include "IO.h"

typedef struct _Qstate Qstate;

void GetNonce(uint8_t * nonce, const uint32_t seed);

void InitQstate(Qstate *s, uint32_t seed);
void NewQstate(Qstate * state);
void CopyQstate(Qstate * state, Qstate * copy);
void FreeQstate(Qstate * state);

void Iteration(Qstate *s);


#endif
