/*
 * Qwyit.h
 *
 * Private Work owned by Qwyit LLC. 
 *
 */

#ifndef PRIMITIVEQ_H_
#define PRIMITIVEQ_H_


void ModEncrypt(const void * k1, const void * k2, void * r);
void ModDecrypt(const void * k1, const void * k2, void * r);

void Combine(const uint8_t * k1, const uint8_t * k2, uint8_t * a1, uint8_t * a2, uint8_t *r);
void Extract(const uint8_t * k, const uint8_t * a, uint8_t *r);

void OneWayCut(const uint8_t * k1, const uint8_t * k2, uint8_t * r);

void ModLock(const uint8_t * k1, const uint8_t * k2, uint8_t * r,  const uint8_t * mask);
void ModUnlock(const uint8_t * k1, const uint8_t * k2, uint8_t * r,  const uint8_t * mask);

#endif
