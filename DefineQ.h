#ifndef DEFINEQ_H_
#define DEFINEQ_H_

#define LENGTH 8

#define WORD 8
#define MOD 1

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

#define MODMASK (1 << MOD)-1
#if MOD == 1
	#define MODMASK_WORD 0x0000000000000000
	#define MODPERBYTE 0x7
#elif MOD == 2
	#define MODMASK_WORD 0x5555555555555555
	#define MODPERBYTE 0x6
#elif MOD == 4
	#define MODMASK_WORD 0x7777777777777777
	#define MODPERBYTE 0x4	
#elif MOD == 8
	#define MODMASK_WORD 0x7F7F7F7F7F7F7F7F
	#define MODPERBYTE 0x0	
#endif

#define MAPSIZE (BLOCKSIZE / 8)
#define ITERATIONMASK ( (1 << ITERATIONSIZE) -1)
#define HASHMASK ( (1 << HASHSIZE) -1)
#define KEYMASK (LENGTH * 8/MOD)-1


//#define Round_p
//#define Iteration_p

#define Primitive_p
//#define Primitive_Extract_p

#include <stdint.h>

//#define BIGENDIAN (*(uint16_t *)"\0\xff" < 0x100)
#define BIGENDIAN (!*(uint8_t *)&(uint16_t){1})

#endif
