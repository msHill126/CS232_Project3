#include "collection.h"

// I suppose if there are no comments in the entire file that could be seen as bad.
// well, the methods are documented in the header, duplicating the comments would've been bad, so here we are.
// I don't think anything here is particularly complex, all I'm trying to do is make a singly linked list.
// ideally, I can use this everywhere in the project I want to use a collection of things, whatever those things are.
// maybe an array or something would be faster in certain cases, but I don't think that's a concern for this
// I did think about implementing both somehow with the same interface... too much effort for this project though.
// honestly this is sort of too much effort for this project, but I wanted to, so meh.

size_t getCount(listElement* list)
{

    listElement* current = list;
    size_t count = 0;

    for(; current!=NULL; count++)
    {
        current = current->next;
    }

    return count;
}


listElement* getElementAt(listElement* list, const size_t index)
{

    listElement* current = list;
    
    for(size_t i = 0;  current!=NULL; i++)
    {
        if(i == index)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;


}


size_t getElementIndex( listElement* list, void* element)
{

    listElement* current = list;
    
    for(size_t i = 0;  current!=NULL; i++)
    {
        if(current->obj == element)
        {
            return i;
        }
        current = current->next;
    }

    return -1;
}



bool removeElement(listElement** list, void* element, bool shouldFree)
{
    return removeElementAt(list, getElementIndex(*list, element), shouldFree);
}


bool removeElementAt(listElement** list, const size_t index, bool shouldFree)
{

    listElement* before = NULL;
    if(index!= 0)
    {
        before = getElementAt(*list, index-1);
    }
    listElement* toRemove = getElementAt(*list, index);

    if(toRemove == NULL) return false;

    listElement* after = toRemove->next;

    if(shouldFree)
    {
        freeType(toRemove->t, toRemove->obj);
    }
    
    free(toRemove);
    

    if(before != NULL)
    {
        before->next = after;
    }
    else
    {
        *list = after;
    }

    return true;
}


bool addElement(listElement** list, const type t, void* obj)
{
    return addElementAt(list, t, obj, getCount(*list));
}


static bool prepend(listElement** list, const type t, void* obj)
{
    // prepending to NULL works too - this is how you should create a list.

    // is this worth being its own method? meh.

    listElement* new = malloc(sizeof(listElement));
    if(new==NULL)
    {
        fprintf(stderr,"malloc failed in prepend.\n");
        return false;
    }

    new->next = *list;
    new->t = t;
    new->obj = obj;

    *list = new;
    return true;
}



bool addElementAt(listElement** list, const type t, void* obj, const size_t index)
{
    if(index == 0)
    {
        return prepend(list, t, obj);
    }

    listElement* before = getElementAt(*list, index-1);

    if(before == NULL)
    {
        // out of bounds.
        fprintf(stderr,"New index '%ld' out of bounds for list size '%ld'.\n", index, getCount(*list));
        return false;
    }

    listElement* after = before->next;

    // after may be null, if we are appending to the end of the list.
    
    listElement* new = malloc(sizeof(listElement));
    if(new==NULL)
    {
        fprintf(stderr,"malloc failed in addElementAt.\n");
        return false;
    }

    new->next = after;
    new->t = t;
    new->obj = obj;

    // correct before
    before->next = new;

    return true;

    
}




void freeList(listElement* list)
{
    if(list == NULL) return;

    // may as well make this one recursive.
    freeType(list->t, list->obj);
    freeList(list->next);
    free(list);
}



void printList(FILE* stream, listElement* list)
{
    fprintf(stream, "%ld element list:\n", getCount(list));

    while(list!=NULL)
    {
        fprintf(stream, "\t");
        printObject(stream, list->t, list->obj);
        fprintf(stream, "\n");
        list = list->next;
    }
}