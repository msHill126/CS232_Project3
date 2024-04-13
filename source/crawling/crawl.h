#ifndef CRAWL_H
#define CRAWL_H

#include "../collection/trie.h"

struct crawlRequest
{
    char* url;
    unsigned int maxHops;
};

struct indexedPage
{
    char* url;
    trieNode* root;
    unsigned int termCount;

};

#endif