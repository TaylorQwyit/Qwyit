#ifndef COMPRESSTREE_H_
#define COMPRESSTREE_H_

#include <stdint.h>

#include "../QwyitCipher/CipherQ.h"
#include "../QwyitCipher/IO.h"

uint8_t * CompressTree(const uint8_t * m, const uint32_t m_len);

#endif
