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
// pagelist is a list of all pages processed by the program so far
// maxPages is the maximum size in pages that pageList can contain. 
void  serviceRequest(crawlRequest* request, listElement** pageList, size_t maxPages);


// index.c


// creates an indexedPage from a url. 
indexedPage* indexPage(char* url);


// scoring.c

// returns the TF-IDF scord of a page according to a lsit of terms
// termList is a list of null terminated strings that consists of only lower case letters.
double score(indexedPage* page, listElement* termList);


#endif