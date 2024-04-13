#include "crawling/crawl.h"
#include "collection/collection.h"
#include "collection/trie.h"
#include "soup/soup.h"

int main(void)
{
    FILE* file = fopen("req.txt", "r");
    if(file==NULL)
    {
        fprintf(stderr,"whoops...\n");
        return 0;
    }

    listElement* reqs = generateRequests(file, 0);
    if(reqs==NULL)
    {
        fprintf(stderr, "Bad format or no entries...\n");
        return 0;
    }
    printList(stdout, reqs);
    freeList(reqs);
    return 0;

}