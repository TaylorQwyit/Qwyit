#ifndef DEFINEQ_H_
#define DEFINEQ_H_

#define LENGTH 32
#define WORD 8
#define WORDMASK 0x77

#define MATCHES 1
#define ITERATIONSIZE 1
#define HASHSIZE 4
#define MESSAGESIZE 100

#define HASHCHARACTERS 32
#define BLOCKSIZE 1
#define BLOCKTRIALS 32

#define MAPSIZE (BLOCKSIZE / 8)
#define ITERATIONMASK ( (1 << ITERATIONSIZE) -1)
#define HASHMASK ( (1 << HASHSIZE) -1)
#define KEYMASK (LENGTH * 2)-1


#define Round_p
#define Iteration_p

#include <stdint.h>

#endif
