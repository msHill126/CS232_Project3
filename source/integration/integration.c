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


bool onlyContainsLower(char* str)
{
    while(*str!='\0')
    {
        if(!islower(*str)&& str!=' ')
        {
            return false;
        }

        str++;
    }

    return true;
}

listElement* parseQuery(char* query)
{
    // okay, we get to do things.
    // unlike the other things we did, which were not things.
    // so it goes.

    // can you tell this project is dragging on?
    // none of this is hard, it's just work.
    // well I suppose the pdf not fully explaining what it expects of me is hard...

    // the testing framework was fun to write...
    // I could make it actually automated
    // never mind that I didn't use it

    // whatever

    // right, parsing queries.

    char* term = strtok(query, " \n");

    if(term==NULL)
    {
        // this should never happen, given the checks we did earlier, but better safe than sorry I guess.
        fprintf(stderr, "Something went wrong parsing your query.\n");
        return;
    }

    // I definitely understand why people invented languages after C
    // there's a nice simplicity to C, though.
    // and it's certainly better than x86 assembly.
    // gcc, of course, doesn't support real mode C afaik
    // but that's not related to anything, now is it?
    // I wonder what arm assembly is like.

    // oh, right, this is supposed to be a source code file.


    listElement* terms = NULL;
    while(term!=NULL)
    {
        char* termObj = malloc(sizeof(char)*(strlen(term)+1));
        if(termObj==NULL) 
        {
            fprintf(stderr, "malloc failed in parseQuery.\n");
            exit(1);
        }

        strncpy(termObj, term, strlen(term)+1);

        if(!addElement(&terms, cstring, termObj))
        {
            fprintf(stderr, "addElement failed in parseQuery.\n");
            exit(1);
        }

        term = strtok(NULL, " \n");
    }

    // yay, this code is done.
    // now I have to call the code I wrote that actually does the thing
    // whoopdie doodle.
    // that doesn't go here though.
    return terms;
}

#define part2BufferSize 1000
// does return.
void part2(listElement* pageList)
{
    while(true)
    {
        char* buffer[part2BufferSize];
        fgets(buffer, part2BufferSize, stdin);

        if(buffer[0]=='\0')
        {
            return;
        }

        if(strlen(buffer)==part2BufferSize-1 && buffer[part2BufferSize-2]!='\n')
        {
            fprintf(stderr, "query too long.\n");
            continue;
        }

        if(!onlyContainsLower(buffer))
        {
            fprintf(stderr, "Please enter a query containing only lower-case letters.\n");
            continue;
        }

        listElement* terms = parseQuery(buffer);
        double* scores = malloc(sizeof(double)*getCount(pageList));
        if(scores==NULL)
        {
            // do I really need to bother with this check?
            fprintf(stderr, "malloc failed in part2.\n");
            exit(1);
        }
        
        // this is an ugly function that I don't like.
        // whatever, nearly done now.

        

        for(int i = 0; i<getCount(pageList); i++)
        {
            // oh, I have to store the top 3 scores.
            // I could be polite and do it in a reasonable way...
            // could use a stack to sort them, that sounds like the least effecient way possible.
            // sure, that'll be new
            // wait, no I don't
            // okay, I need to make a double counter
            // that wasn't english
            // need to register doubles with lists, then just, you know, print out the list
            // don't really need to sort the list
            // or just make an array?
            // I'll just do that, that's much less effort.

            // guh
            indexedPage* page = getElementAt(pageList, i);
            scores[i]=score(page, terms);
        }

        // do things
    }
}

