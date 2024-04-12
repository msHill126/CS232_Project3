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
