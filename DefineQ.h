#ifndef DEFINEQ_H_
#define DEFINEQ_H_

#define LENGTH 4

#define WORD 64 //8,16,32, or 64 
#define MOD 1 //1,2,4, or 8

#define MESSAGESIZE 100

//#define Round_p
//#define Iteration_p

#define Primitive_p
//#define Primitive_Extract_p


//******** No Changes Below Here ********
#include <stdint.h>
#if (WORD == 64)
	#define WORDMASK 0xFFFFFFFFFFFFFFFF
	typedef struct{uint64_t * p;}Pointer;
#elif (WORD == 32)
	#define WORDMASK 0xFFFFFFFF
	typedef struct{uint32_t * p;}Pointer;
#elif (WORD == 16)
	#define WORDMASK (1 << WORD)-1
	typedef struct{uint16_t * p;}Pointer;
#elif (WORD == 8)
	#define WORDMASK (1 << WORD)-1
	typedef struct{uint8_t * p;}Pointer;
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


//#define BIGENDIAN (*(uint16_t *)"\0\xff" < 0x100)
#define BIGENDIAN (!*(uint8_t *)&(uint16_t){1})

#endif
