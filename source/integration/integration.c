#include "integration.h"



listElement* part1(int argc, char* argv[])
{
    if(argc!=4)
    {
        fprintf(stderr, "bad usage. Expected: url maxPages rngSeed\n");
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");
    if(file==NULL)
    {
        fprintf(stderr, "Couldn't open file '%s'.\n", argv[1]);
        exit(1);
    }

    // think an implicit cast from a long to unsigned long is okay?
    size_t maxPages = atol(argv[2]);

    if(maxPages<=0)
    {
        fprintf(stderr, "Max pages must be greater than 0. It was '%lu'.\n", maxPages);
        exit(1);
    }

    srand(atoi(argv[3]));

    // okay, do the thing
    listElement* reqs = generateRequests(file, 0);
    if(reqs==NULL)
    {
        fprintf(stderr, "Bad format or no entries in file '%s'.\n", argv[1]);
        exit(1);
    }

    printf("Indexing...\n");
    // let's treat a linked list like an array again for no reason.

    int requestCount = getCount(reqs);
    listElement* pageList = NULL;
    for(int i = 0; i<requestCount; i++)
    {
        serviceRequest((crawlRequest*)(getElementAt(reqs, i)->obj), &pageList, maxPages);
    }

   
    freeList(reqs);

   

    return pageList;
}
