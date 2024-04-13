#include "collection.h"
#include "trie.h"


// free an object of a given type.
void freeType(const type t, void* obj)
{
    if(obj == NULL)
    {
        return;
    }

    switch (t)
    {
    
        trie_node:
            freeNode((trieNode*)obj);
        default:
            free(obj);
            return;
    }
}


void printObject(FILE* stream, const type t, void* obj)
{
    if(obj == NULL)
    {
        fprintf(stream, "NULL");
        return;
    }

    switch (t)
    {
    
        case integer:
            fprintf(stream, "%d", *(int*)obj);
            return;
        case cstring:
            fprintf(stream, "%s", (char*)obj);
            return;
        default:
            fprintf(stream, "Unknown Type '%d'",t);
            return;
    }

}
