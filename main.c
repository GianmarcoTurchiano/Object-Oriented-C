#include <stdio.h>
#include <stdlib.h>
#include "object.h"

int main(void)
{
    void *arr[] = {
        newObject(),
        &Class,
        newPoint(4, 16),
        &Object,
        newObject(),
        &Point,
    };

    size_t arr_len = sizeof(arr) / sizeof(arr[0]);

    for (size_t i = 0; i < arr_len; i++)
    {
        printf("Iteration #%ld: ", i);
        print(arr[i]);
    }
   
    return EXIT_SUCCESS;
}