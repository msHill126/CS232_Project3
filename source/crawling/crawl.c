#include "crawl.h"
#include "../soup/soup.h"
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


static bool containsURL(char* url, listElement* pageList)
{
    // it's not effecient to do so, but we're going to iterate through the list like an array because we can.
    // wee, abstraction
    // could just use the next member of the struct, but that's no fun, not at all.

    int listSize = getCount(pageList);
    
    for(int i = 0; i<listSize; i++)
    {
        // this would never cause a weird memory error that will be hard to track down. It's fine.
        // I mean I made the generic list implementation knowing this would happen
        // there's a reason void* isn't the safest thing in the world...
        char* listUrl =((indexedPage*)(getElementAt(pageList, i)->obj))->url;
        // unrelated, but apparently on windows 11 (or something, not entirely sure), segfaults don't print a message
        // the program just hangs for a while before exiting.
        // might be nice if it did, just saying...
        // well, I'm writing all of this in linux anyways so whatever


        if(strcmp(url, listUrl) == 0)
        {
            return true;
        }
    }

    return false;
}


// returns if a page was successfully indexed.
static bool indexNewPage(char* url, listElement** pageList, size_t maxPages)
{
    
    if(containsURL(url, *pageList)) return false;

    // I probably need to check this before generating the url using getLink because that will
    // advance the rng..
    if(getCount(*pageList)>=maxPages) return false;
    

    indexedPage* page = indexPage(url);
    //if(page==NULL) return false; // we, apparently, want to add pages that we couldn't index into calculations.
                                   // not sure why, but that's how the 'correct' program appears to do it.
                                   // the pdf isn't specific enough for me to dispute the program, so...
    
    if(!addElement(pageList, indexed_page, page)) exit(1);

    return true;
}



void serviceRequest(crawlRequest* request, listElement** pageList, size_t maxPages)
{
    indexNewPage(request->url, pageList, maxPages);


    char* currentURL = request->url; // so the instructions on the pdf were not clear on this.
    // apparently, you wanted each successive call to getlink to have the previous url, instead of the first url
    // the psudocode in the pdf didn't fully clarify this (should've set url=new_url), and so I had to guess what the code meant.
    // at least it's not hard to fix

    int hopsAttempted = 0;
    while(getCount(*pageList)<maxPages && hopsAttempted<request->maxHops)
    {

        char newURL[1000];
        if(!getLink(currentURL, newURL, 1000)) return;
     
        currentURL = newURL;
        indexNewPage(currentURL, pageList, maxPages); // we don't care whether this worked or not.
        hopsAttempted++;
       

    }
}