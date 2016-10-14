#ifndef DEFINEQ_H_
#define DEFINEQ_H_

#define LENGTH 8 //bytes

#define WORD 8 //8,16,32, or 64 bits 
#define MOD 1 //1,2,4,8,16,32, or 64 bits
#define TREE 4

#define MESSAGESIZE 64  //in Bytes

//#define Round_p
#define Iteration_p

//#define Primitive_p
//#define Primitive_Extract_p

#define CompressTree_p

//******** No Changes Below Here ********
#include <stdint.h>
#include <stdlib.h>

#define WORDPERLENGTH (LENGTH / (WORD / 8))

#define MODMASK ((1 << MOD)-1)
#define KEYMASK ((LENGTH * 8/MOD)-1)

#if MOD == 1
	#define MODMASK_WORD 0x0000000000000000
	#define MPW 0x7F
#elif MOD == 2
	#define MODMASK_WORD 0x5555555555555555
	#define MPW 0x7E
#elif MOD == 4
	#define MODMASK_WORD 0x7777777777777777
	#define MPW 0x7C
#elif MOD == 8
	#define MODMASK_WORD 0x7F7F7F7F7F7F7F7F
	#define MPW 0x78
#elif MOD == 16
	#define MODMASK_WORD 0x7FFF7FFF7FFF7FFF
	#define MPW 0x70
#elif MOD == 32
	#define MODMASK_WORD 0x7FFFFFFF7FFFFFFF
	#define MPW 0x60
#elif MOD == 64
	#define MODMASK_WORD 0x7FFFFFFFFFFFFFFF
	#define MPW 0x40
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

#define MODPERWORD (((1 << WORDMASK) - 1) & MPW)
#define TREEMASK ((1 << TREE) - 1)

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
