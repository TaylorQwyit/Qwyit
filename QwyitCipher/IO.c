
#include "../DefineQ.h"
#include "IO.h"

#include <stdio.h>

void PrintArray(const uint8_t * array, const uint32_t length)
{
        uint32_t i;
        for(i = 0; i < length; i++)
        {
                printf("%02x",array[i]);

        }
        printf("\n");
}

