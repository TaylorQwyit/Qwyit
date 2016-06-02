/*
 * Qwyit.h
 *
 * Private Work owned by Qwyit LLC. 
 *
 */

#ifndef PRIMATIVEQ_H_
#define PRIMATIVEQ_H_

void ModEncrypt(const uint8_t * k1, const uint8_t * k2, uint8_t * r);

void ModDecrypt(const uint8_t * k1, const uint8_t * k2, uint8_t * r);

void Combine(const uint8_t * k1, const uint8_t * k2, uint8_t * a1, uint8_t * a2, uint8_t *r);

void Extract(const uint8_t * k, const uint8_t * a, uint8_t *r);

void OneWayCut(const uint8_t * k1, const uint8_t * k2, uint8_t * r);

#endif
