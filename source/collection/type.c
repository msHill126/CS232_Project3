#include "collection.h"


// free an object of a given type.
void freeType(const type t, void* obj)
{
    if(obj == NULL)
    {
        return;
    }

    switch (t)
    {
    
   
        default:
            free(obj);
            return;
    }
}


void printObject(FILE* stream, const type t, const void* obj)
{
    if(obj == NULL)
    {
        fprintf(stream, "NULL");
        return;
    }

    switch (t)
    {
    
        case integer:
            fprintf(stream, "%d", obj);
            return;
        case cstring:
            fprintf(stream, "%s", obj);
            return;
        default:
            fprintf(stream, "Unknown Type '%d'",t);
            return;
    }

}
