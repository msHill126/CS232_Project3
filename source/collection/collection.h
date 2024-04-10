#ifndef COLLECTION_H
#define COLLECTION_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

enum type
{
    integer,    
    cstring
};

typedef enum type type;


struct listElement
{
    type t;
    struct listElement* next;
    void* obj;
};

typedef struct listElement listElement;



// free an object of a given type.
void freeType(const type t, void* obj);

void printObject(FILE* stream, const type t, const void* obj);

// list element functions



size_t getCount(const listElement* list);
// returns the number of elements in the list starting from element.
// list may be null, in which case, getCount returns 0.

listElement* getElementAt(const listElement* list, const size_t index);
// returns the element at index index in list list.
// returns null if the index is out of bounds.

size_t getElementIndex(const listElement* list, const listElement* element);
// returns the index of element element in a list who's first element is list.
// returns -1 if list does not contain element or either are null.


bool removeElement(listElement** list, listElement* element);
// removes a particular element from the list and frees it.

bool removeElementAt(listElement** list, const size_t index);
// removes an element at a particular index from the list.

bool addElement(listElement** list, const type t, const void* obj);
// equivalent to addElementAt(list, t, obj, getCount(list));

bool addElementAt(listElement** list, const type t, const void* obj, const size_t index);
// adds an element at a particular index.
// *list may be null. if *list is null and index is 0, then a new list will be created, and *list is modified.

void freeList(listElement* list);
// frees all list elements and the objects held in the list.

listElement* arrayToList(const type t, void* objects[]);
// creates a new list from an array. All objects are expected to have the same type.
// returns null on failure.

void printList(FILE* stream, listElement* list);





#endif