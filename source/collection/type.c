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
        case page_score:
            free(obj); // don't care about freeing the page, so we do this.
            break;
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
        case doublefloat:
            fprintf(stream, "%f", *(double*)obj);
            return;
        case crawl_request:
            printRequest(stream, obj);
            return;
        case indexed_page:
            printPage(stream, obj); // wonder if the compiler will yell at me for not casting the void pointer... (probably)
            return;
        case page_score:
            printScore(stream, obj); // apparently it's fine, past self. that seems like an easy way for things to mysteriously break.
            break;
        default:
            fprintf(stream, "Unknown Type '%d'",t);
            return;
    }

}
