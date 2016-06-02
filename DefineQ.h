#ifndef DEFINEQ_H_
#define DEFINEQ_H_

#define LENGTH 8

#define WORD 64
#define MOD 4

#define MATCHES 1
#define ITERATIONSIZE 1
#define HASHSIZE 4
#define MESSAGESIZE 100

#define HASHCHARACTERS 32
#define BLOCKSIZE 1
#define BLOCKTRIALS 32

#if (WORD > 32)
	#define WORDMASK 0xFFFFFFFFFFFFFFFF
#elif (WORD == 32)
	#define WORDMASK 0xFFFFFFFF
#else
	#define WORDMASK (1 << WORD)-1
#endif

#define MODMASK_WORD 0x7777777777777777
#define MODMASK (1 << MOD)-1

#define MAPSIZE (BLOCKSIZE / 8)
#define ITERATIONMASK ( (1 << ITERATIONSIZE) -1)
#define HASHMASK ( (1 << HASHSIZE) -1)
#define KEYMASK (LENGTH * 2)-1


//#define Round_p
//#define Iteration_p

#define Primative_p

#include <stdint.h>

//#define BIGENDIAN (*(uint16_t *)"\0\xff" < 0x100)

#define BIGENDIAN (!*(uint8_t *)&(uint16_t){1})

#endif
