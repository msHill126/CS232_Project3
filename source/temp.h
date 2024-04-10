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


// it definitely occurs to me that I could use void* for these sorts of data type structs,
// and then maybe make an enum for data type to put in the struct for error checking...
// not sure if it's a good idea but seems like it'd remove tedium to some degree

// of course, to manage things well, I'd need some generic array_free method with a switch statement for each type, and one to create the array, too.
// A giant switch statement would be gross, so I'd want to make something with function pointers that lets me register these things, maybe a function in each header file that adds new structs.

// having a generic array like that would be pretty useful, especially since I'd be able to know the types of things at runtime...
// it might also be useful to know the types of the structs themselves at runtime, so it wouldn't be hard to make a generic 'reference' struct,
// and I could add functions to construct and free them as well...
// maybe it would be convienent to add additional parameters to those methods... I think it could be done with C's equivalent of varargs
// of course the regeristing code would have to check that the parameters were of the correct types

// it might also be convienent if I could have functions that act on a reference of a specific type, maybe tie it to the type itself with function pointers or something
// but in order to give those functions unique names, I'd have to associate them with strings...
// that's inconvienent

// maybe I could add some sort of preprocessing, then, that allowed me to reference a type or reference's functions as normal, which then gets converted into the appropriate C code...
// this could potentially make regeristing much simpler as well - whole files that represent a type could be processed into mostly regeristing code, and types could be checked during proccessing
// as well, instead of at runtime (or maybe both?)

// although this would probably make casting pretty complicated...
// wait, is this how C++ came to be?

// well, that seems to be a pretty strong 'if you give a mouse a cookie' situation, so I'll be wary then...
// I still need to actually learn C++ sooner or later.


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

void freePages(indexedPageArray* arr);

void freeRequests(crawlRequestArray* arr);

// Maybe 'soup.h?'



int getLink(const char* srcAddr, char* link, const int maxLinkLength);
/*
 * srcAddr should be a web address (e.g., http://www.yahoo.com).
 * link should point to an array of maxLinkLength characters.
 * getLink returns 1 if a link was found and 0 otherwise.
 * If a link was found, "link" will be filled in with the web address.
 */


int getText(const char* srcAddr, char* buffer, const int bufSize);
/*
*   unknown.
*/
