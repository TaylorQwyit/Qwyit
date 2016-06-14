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

void Combine(const void * k1, const void * k2, void * a1, void * a2, void *r);
void Extract(const void * k, const void * a, void *r);

void OneWayCut(const uint8_t * k1, const uint8_t * k2, uint8_t * r);

void ModLock(const uint8_t * k1, const uint8_t * k2, uint8_t * r,  const uint8_t * mask);
void ModUnlock(const uint8_t * k1, const uint8_t * k2, uint8_t * r,  const uint8_t * mask);

#endif
