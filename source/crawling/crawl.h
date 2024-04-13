#ifndef CRAWL_H
#define CRAWL_H

#include "../collection/collection.h"
#include "../collection/trie.h"

struct crawlRequest
{
    char* url;
    unsigned int maxHops;
};

typedef struct crawlRequest crawlRequest;

struct indexedPage
{
    char* url;
    trieNode* root;
    unsigned int termCount;

};

typedef struct indexedPage indexedPage;


// structs.c

/* creates a new crawlRequest struct.
 returns null on failure.*/
crawlRequest* newRequest(char* url, unsigned int maxHops);

// frees a request along with its url.
void freeRequest(crawlRequest* request);


void printRequest(FILE* stream, crawlRequest* request);

void freePage(indexedPage* page);

void printPage(FILE* stream, indexedPage* page);


// crawl.c

// reads file contents and creates an array of crawlRequests. if *bufferSize is 0, all requests will be made and bufferSize updated to reflect how many were made.
// if it is nonzero, then at most bufferSize requests will be made. Returns NULL on failure or if the file was empty.
// list of crawlRequests is returned on success. NULL on failure.
listElement* generateRequests(FILE* file, int maxCount);

// resizes buffer to fit requests and appends them to the buffer at startingIndex.
// returns 0 on failure.
bool serviceRequest(crawlRequest* request, listElement* pageList);

// creates an indexedPage from a url. Returns NULL on failure.
indexedPage* indexPage(char* url);




#endif