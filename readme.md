# Is C an object-oriented language?

No. Of course it isn't.

...

However, this C code illustrates how inheritance and inclusion polymorphism are very simple consequences of pointer arithmetic and of late binding function calls respectively.

**DISCLAIMER: This is only for educational purposes. Programming in C in this style is obviously not recommended.**

The base `struct Object` only contains a pointer to a `struct Class`.

```
struct Object
{
    struct Class *class;    
};
```

Any other class is an extension of the class of objects, meaning that the corresponding data types have to list an instance of `struct Object` as their first property.

```
struct Point
{
    struct Object _;
    float x, y;
};
```

Passing a pointer to an instance of `struct Point` to a function that is expecting a pointer to an instance of `struct Object` means that the first will be correctly interpreted as an instance of the class of objects. In other words, the properties which are exclusive to `struct Point` will be simply ignored, making it possible for the instances of the class of points to expose the same interface of the class of objects.

The `struct Class` is itself an extension of the class of objects

```
struct Class
{
    struct Object _;
    struct Class *super;
    const char *name;
    void (*print)(void*);
};
```

The instances of the class of classes are Java-style "meta-classes", i.e. objects that stand for classes. Each class corresponds to an instance of the `struct Class`.

```
struct Class Object = {
    .name = "Object",
    .super = NULL,
    ._ = {
        .class = &Class,
    },
    .print = printObject
};

struct Class Class = {
    .name = "Class",
    .super = &Object,
    ._ = {
        .class = &Class,
    },
    .print = printClass
};

struct Class Point = {
    .name = "Point",
    .super = &Object,
    ._ = {
        .class = &Class
    },
    .print = printPoint
};
```

Each instance of the class of classes points to the instance of its super class, as well as to a different function for printing out their corresponding objects. Each class refers to a different, specialized `.print` method, which is dispatched dynamically by the generic `print()` function.

```
void print(struct Class **self)
{
    (**self).print(self);
}
```

When this function is called on a pointer to a `struct Object`, or any of its extensions, the argument will be reinterpreted as a pointer to a pointer to `struct Class`. In fact, the first `sizeof(struct Class*)` bytes of any object are guaranteed to correspond to a `struct Class*`. The `.print()` method is then called onto that same pointer, which will be downcasted appropriately by the pointed implementation.

```
static void printObject(void *self)
{
    printf("<%s: %p>\n", ((struct Object*) self)->class->name, self);
}

static void printClass(void *self)
{
    printf("(%s) ", ((struct Class*) self)->name);
    ((struct Class*) self)->_.class->super->print(self);
}

static void printPoint(void *self)
{
    printf("x: %f, y: %f\n", ((struct Point*) self)->x, ((struct Point*) self)->y);
}
```

In the `main()`, an array containing pointers to instances of different classes is iterated over, with `print()` being called onto each of its elements in order to display polymorphic behaviour.

```
Iteration #0: <Object: 0x55d8712f42a0>
Iteration #1: (Class) <Class: 0x55d870b40040>
Iteration #2: x: 4.000000, y: 16.000000
Iteration #3: (Object) <Class: 0x55d870b40020>
Iteration #4: <Object: 0x55d8712f42e0>
Iteration #5: (Point) <Class: 0x55d870b40060>
```
