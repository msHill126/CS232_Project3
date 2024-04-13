// this is a 'header file' where I plan out what structs and such I intend to use


struct crawlRequest
{
    char* url;
    unsigned int maxHops;
};

// getting used to C a bit more... I made a program consisting only of linked lists,
// Now I guess I'm seeing how I might do arrays... we'll see how it goes.
struct crawlRequestArray
{
    unsigned int count;
    crawlRequest* arr; // indexing would be like array->cr[12]
};



struct indexedPage
{
    char* url;
    trieNode* root;
    unsigned int termCount;

};

struct indexedPageArray
{
    unsigned int count;
    indexedPage* arr;
};


// reads file contents and creates an array of crawlRequests. if *bufferSize is 0, all requests will be made and bufferSize updated to reflect how many were made.
// if it is nonzero, then at most bufferSize requests will be made. Returns NULL on failure or if the file was empty.
crawlRequestArray* generateRequests(FILE* file, int* maxCount);

// resizes buffer to fit requests and appends them to the buffer at startingIndex.
// returns 0 on failure.
bool serviceRequest(crawlRequest* request, indexedPageArray* arr);

// creates an indexedPage from a url. Returns NULL on failure.
indexedPage* indexPage(char* url);

void freePage(indexedPage* page);


// Maybe 'soup.h?'



