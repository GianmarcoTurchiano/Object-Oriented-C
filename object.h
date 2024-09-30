#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdbool.h>
#include <stdio.h>

struct Object;
struct Class;
struct Point;

extern struct Class Class;
extern struct Class Object;
extern struct Class Point;

struct Object* newObject(void);
struct Point* newPoint(float x, float y);
void print(struct Class**);

#endif