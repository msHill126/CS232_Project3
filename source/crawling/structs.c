// my headers are set up in a stupid way...
// in an earilier C project I did, I had all my headers in one folder, then I had folders for each header where the C files lived
// not sure if that was better but dependencies might've been easier to see...
#include "crawl.h" 


/* creates a new crawlRequest struct. 
 returns null on failure.*/
crawlRequest* newRequest(char* url, unsigned int maxHops)
{
    crawlRequest* req = malloc(sizeof(crawlRequest));
    if(req == NULL)
    {
        fprintf(stderr, "Malloc failed in newRequest.");
        return NULL;
    }

    req->maxHops = maxHops;
    req->url = malloc(sizeof(char)*(strlen(url)+1));

    if(req->url == NULL)
    {
        fprintf(stderr, "Malloc failed in newRequest.");
        free(req);
        return NULL;
    }

    strncpy(req->url, url, strlen(url)+1);
    return req;
}

// frees a request along with its url.
void freeRequest(crawlRequest* request)
{
    if(request==NULL) return;
    free(request->url);
    free(request);
}

void freePage(indexedPage* page)
{
    if(page==NULL) return;
    freeNode(page->root);
    free(page->url);
    free(page);
}


// man, if only there were some convienent, like, tostring or something...
// there's a reason people don't write a ton of apps in straight C, I can tell that.
// lots of busy work, easy to break something in a mysterious way...
// I mean I would've had to do this in a language like java too, but at least there's a standardized way to get this for all objects...
// didn't have to write a new method stub in a header and whatnot... @override...
void printRequest(FILE* stream, crawlRequest* request)
{
    fprintf(stream, "CrawlRequest to \"%s\" Max Hops: %d\n", request->url, request->maxHops);
}



void printPage(FILE* stream, indexedPage* page)
{
    fprintf(stream, "Page: \"%s\"\nTotal terms: %d\n", page->url, page->termCount);
    printTrie(stream, page->root);
}



void printScore(FILE* stream, pageScore* score)
{
    fprintf(stream, "%s (score: %.4f)", score->page->url, score->score );
}
