#ifndef DEFINEQ_H_
#define DEFINEQ_H_

#define LENGTH 8 //bytes

#define WORD 8 //8,16,32, or 64 bits 
#define MOD 4 //1,2,4, or 8 bits
#define TREE 8

#define MESSAGESIZE 128 //in Bits

//#define Round_p
//#define Iteration_p

#define Primitive_p
//#define Primitive_Extract_p

//******** No Changes Below Here ********
#include <stdint.h>
#include <stdlib.h>

#define WORDPERLENGTH (LENGTH / (WORD / 8))

#define MODMASK ((1 << MOD)-1)
#define KEYMASK ((LENGTH * 8/MOD)-1)
#define WORD_MASK (1<<WORD)

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

#if (WORD == 64)
 #define WORDMASK 6
 typedef struct{uint64_t * p;}Pointer;
 typedef struct{const uint64_t * p;}ConstPointer;
 typedef struct{uint64_t w;}Word;
#elif (WORD == 32)
 #define WORDMASK 5
 typedef struct{uint32_t * p;}Pointer;
 typedef struct{const uint32_t * p;}ConstPointer;
 typedef struct{uint32_t w;}Word;
#elif (WORD == 16)
 #define WORDMASK 4
 typedef struct{uint16_t * p;}Pointer;
 typedef struct{const uint16_t * p;}ConstPointer;
 typedef struct{uint16_t w;}Word;
#elif (WORD == 8)
 #define WORDMASK 3
 typedef struct{uint8_t * p;}Pointer;
 typedef struct{const uint8_t * p;}ConstPointer;
 typedef struct{uint8_t w;}Word;
#endif

#define MAPSIZE (BLOCKSIZE / 8)
#define ITERATIONMASK ( (1 << ITERATIONSIZE) -1)
#define HASHMASK ( (1 << HASHSIZE) -1)

#define BIGENDIAN (!*(uint8_t *)&(uint16_t){1})

static inline Pointer AllocPointer(const uint32_t size)
{
  Pointer memPointer;
  memPointer.p =  malloc(size*sizeof(*memPointer.p) );
  return memPointer;
}

static inline Pointer AllocBytes(const uint32_t size)
{
  Pointer memPointer;
  memPointer.p =  malloc(size*sizeof(uint8_t));
  return memPointer;
}

#endif
