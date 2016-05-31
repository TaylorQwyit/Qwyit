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

#define WORDMASK (1 << WORD)-1
#define MODMASK 0x77

#define MAPSIZE (BLOCKSIZE / 8)
#define ITERATIONMASK ( (1 << ITERATIONSIZE) -1)
#define HASHMASK ( (1 << HASHSIZE) -1)
#define KEYMASK (LENGTH * 2)-1


//#define Round_p
//#define Iteration_p

//#define Primative_p

#include <stdint.h>

#endif
