#include "crawling/crawl.h"
#include "collection/collection.h"
#include "collection/trie.h"
#include "soup/soup.h"

/*int main(void)
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

}*/


// temporary, I swear!
int main(int argc, char* argv[])
{
    if(argc!=4)
    {
        fprintf(stderr, "bad usage. Expected: url maxPages rngSeed\n");
    }

    FILE* file = fopen(argv[1], "r");
    if(file==NULL)
    {
        fprintf(stderr, "Couldn't open file '%s'.\n", argv[1]);
        return 1;
    }

    // think an implicit cast from a long to unsigned long is okay?
    size_t maxPages = atol(argv[2]);

    if(maxPages<=0)
    {
        fprintf(stderr, "Max pages must be greater than 0. It was '%lu'.\n", maxPages);
        return 1;
    }

    srand(atol(argv[3]));

    // okay, do the thing
    listElement* reqs = generateRequests(file, 0);
    if(reqs==NULL)
    {
        fprintf(stderr, "Bad format or no entries in file '%s'.\n", argv[1]);
        return 1;
    }

    // let's treat a linked list like an array again for no reason.

    int requestCount = getCount(reqs);
    listElement* pageList = NULL;
    for(int i = 0; i<requestCount; i++)
    {
        serviceRequest((crawlRequest*)(getElementAt(reqs, i)->obj), &pageList, maxPages);
    }

   
    freeList(reqs);

   // printList(stdout, pageList);

    freeList(pageList);

    return 0;
}


    
