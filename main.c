#include <stdio.h>
#include <stdlib.h>
#include "object.h"

int main(void)
{
    struct Object *obj1 = newObject();

    if (!obj1)
    {
        return EXIT_FAILURE;
    }

    struct Object *obj2 = newObject();
    
    if (!obj2)
    {
        return EXIT_FAILURE;
    }
    struct Point *pnt = newPoint(4, 16);

    if (!pnt)
    {
        return EXIT_FAILURE;
    }

    void *arr[] = {
        obj1,
        &Class,
        pnt,
        &Object,
        obj2,
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