#include "crawl.h"
#include <string.h>

static char* getLastSpace(char* line)
{
    char* toRet = NULL;
    while((*line)!='\0')
    {
        if(*line==' ')
        {
            toRet=line;
        }

        line++;
    }
    return toRet;
}


static crawlRequest* getRequest(char* line)
{
    char* last = getLastSpace(line);
    if(last==NULL)
    {
        fprintf(stderr,"Input was in invalid format. Expected format per line: 'link/to/page with/spaces.example number'.\n");
        return NULL;
    }
    *last='\0'; 

    last++;
    int hops = 0;
    sscanf(last, "%d\n", &hops);

    if(!hops)
    {
        fprintf(stderr,"Input was in invalid format. Expected format per line: 'link/to/page with/spaces.example number'.\n number may not be 0 or less.\n");
        return NULL;
    }

    return newRequest(line, hops);

}

static bool hasContent(char* line)
{
    while(*line!='\0')
    {
        if(!isspace(*line))
        {
            return true;
        }
        line++;
    }

    return false;
}

listElement* generateRequests(FILE* file, int maxCount)
{
    char lineBuffer[1000];
    listElement* requests = NULL;
    size_t requestCount = 0;

    while((maxCount == 0 || requestCount<maxCount)&&(!feof(file)))
    {
        if(!fgets(lineBuffer, 1000, file)) break;
        if(!hasContent(lineBuffer)) continue;

        crawlRequest* req = getRequest(lineBuffer);
        if(req==NULL)
        {
            // clean up, panic, leave, etc.
            fclose(file);
            freeList(requests);
            return NULL;
        }

        if(!addElement(&requests, crawl_request, req))
        {
            // clean up, panic, leave, etc.
            fclose(file);
            freeList(requests);
            return NULL;
        }
        
        requestCount++;
    }

    fclose(file);
    return requests;
}
