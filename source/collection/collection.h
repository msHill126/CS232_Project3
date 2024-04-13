#ifndef COLLECTION_H
#define COLLECTION_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


// it definitely occurs to me that I could use void* for these sorts of data collection structs,
// and then maybe make an enum for data type to put in the struct for error checking...
// not sure if it's a good idea but seems like it'd remove tedium to some degree

// of course, to manage things well, I'd need some generic array_free method with a switch statement for each type, and one to create the array, too.
// A giant switch statement would be gross, so I'd want to make something with function pointers that lets me register these things, maybe a function in each header file that adds new structs.

// having a generic array like that would be pretty useful, especially since I'd be able to know the types of things at runtime...
// it might also be useful to know the types of the structs themselves at runtime, so it wouldn't be hard to make a generic 'reference' struct,
// and I could add functions to construct and free them as well...
// maybe it would be convienent to add additional parameters to those methods... I think it could be done with C's equivalent of varargs
// of course the regeristing code would have to check that the parameters were of the correct types

// it might also be convienent if I could have functions that act on a reference of a specific type, maybe tie it to the type itself with function pointers or something
// but in order to give those functions unique names, I'd have to associate them with strings...
// that's inconvienent

// maybe I could add some sort of preprocessing, then, that allowed me to reference a type or reference's functions as normal, which then gets converted into the appropriate C code...
// this could potentially make regeristing much simpler as well - whole files that represent a type could be processed into mostly regeristing code, and types could be checked during proccessing
// as well, instead of at runtime (or maybe both?)

// although this would probably make casting pretty complicated...
// wait, is this how C++ came to be?

// well, that seems to be a pretty strong 'if you give a mouse a cookie' situation, so I'll be wary then...
// I still need to actually learn C++ sooner or later.

// Later: I wote a lot of stuff I didn't need to
// luckily I prevented myself from fully writing a bad automated testing framework
// or did I?



enum type
{
    integer,    
    cstring,
    trie_node
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

void printObject(FILE* stream, const type t, void* obj);



// list element functions

size_t getCount( listElement* list);
// returns the number of elements in the list starting from element.
// list may be null, in which case, getCount returns 0.

listElement* getElementAt( listElement* list, const size_t index);
// returns the element at index index in list list.
// returns null if the index is out of bounds.

size_t getElementIndex(listElement* list, void* element);
// returns the index of element element in a list who's first element is list.
// returns -1 if list does not contain element or either are null.


bool removeElement(listElement** list, void* element);
// removes a particular element from the list and frees it.

bool removeElementAt(listElement** list, const size_t index);
// removes an element at a particular index from the list.

bool addElement(listElement** list, const type t, void* obj);
// equivalent to addElementAt(list, t, obj, getCount(list));

bool addElementAt(listElement** list, const type t, void* obj, const size_t index);
// adds an element at a particular index.
// *list may be null. if *list is null and index is 0, then a new list will be created, and *list is modified.

void freeList(listElement* list);
// frees all list elements and the objects held in the list.

void printList(FILE* stream, listElement* list);



#endif