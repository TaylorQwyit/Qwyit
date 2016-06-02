
#include "../DefineQ.h"
#include "IO.h"

#include <stdio.h>

void PrintCharArray(const uint8_t * array, const uint32_t length)
{
        uint32_t i;
        for(i = 0; i < length; i++)
        {
                printf("%02x",array[i]);

        }
        printf("\n");
}

void PrintArray(const uint64_t * array, const uint32_t length)
{
        uint32_t i;
        for(i = 0; i < length; i++)
        {
                printf("%016lx",array[i]);

        }
        printf("\n");
}


