#include "collection.h"
#include "trie.h"
#include "../crawling/crawl.h"


// free an object of a given type.
void freeType(const type t, void* obj)
{
    if(obj == NULL)
    {
        return;
    }

    switch (t)
    {
    
        case trie_node:
            freeNode((trieNode*)obj);
            return;
        case crawl_request:
            freeRequest((crawlRequest*)obj);
            return;
        case indexed_page:
            freePage((indexedPage*)obj);
            return;
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
        case crawl_request:
            printRequest(stream, obj);
            return;
        case indexed_page:
            printPage(stream, obj); // wonder if the compiler will yell at me for not casting the void pointer... (probably)
            return;
        default:
            fprintf(stream, "Unknown Type '%d'",t);
            return;
    }

}
