#include "object.h"
#include <stdlib.h>

struct Object
{
    struct Class *class;    
};

struct Class
{
    struct Object _;
    struct Class *super;
    const char *name;
    void (*print)(void*);
};

void print(struct Class **self)
{
    (**self).print(self);
}

struct Object* newObject()
{
    struct Object *self = malloc(sizeof(*self));

    self->class = &Object;

    return self;
}

static void printObject(void *self);

struct Class Object = {
    .name = "Object",
    .super = NULL,
    ._ = {
        .class = &Class,
    },
    .print = printObject
};

static void printObject(void *self)
{
    printf("<%s: %p>\n", ((struct Object*) self)->class->name, self);
}

static void printClass(void *self);

struct Class Class = {
    .name = "Class",
    .super = &Object,
    ._ = {
        .class = &Class,
    },
    .print = printClass
};

static void printClass(void *self)
{
    printf("(%s) ", ((struct Class*) self)->name);
    ((struct Class*) self)->_.class->super->print(self);
}

struct Point
{
    struct Object _;
    float x, y;
};

struct Point* newPoint(float x, float y)
{
    struct Point *self = malloc(sizeof(*self));

    self->_.class = &Point;
    
    self->x = x;
    self->y = y;

    return self;
}

static void printPoint(void *self);

struct Class Point = {
    .name = "Point",
    .super = &Object,
    ._ = {
        .class = &Class
    },
    .print = printPoint
};

static void printPoint(void *self)
{
    printf("x: %f, y: %f\n", ((struct Point*) self)->x, ((struct Point*) self)->y);
}