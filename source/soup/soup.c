#include "soup.h"
#include <string.h>
#include <stdlib.h>

// essentially I copied over the functions that handled the python scripts from project 1 and 2
// I refactored them, figured I may as well know what they do. instead of just trusting a magical
// black box.
// didn't really look at the python scripts though, because I'm lazy. 

static FILE* getPipe(const char* srcAddr, char* cmdBuffer, char* pythonScript, int bufferSize)
{

    snprintf(cmdBuffer, bufferSize, "curl -s \"%s\" | python3 %s.py", srcAddr, pythonScript);
    FILE* pipe = popen(cmdBuffer, "r");
    if(pipe ==NULL)
    {
        fprintf(stderr, "ERROR: could not open the pipe for command %s\n", cmdBuffer);
        exit(-1);
    }
    return pipe;

}

static void getRandomLine(char* buffer, size_t bufSize, FILE* stream, size_t numLines)
{

    // get a random number between 0 and 1 (I think)
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    // get the nth link until n/total links > r
    for(int linkNum=0; linkNum<numLines; linkNum++)
    {
        fgets(buffer, bufSize, stream);
        
        if(r < (linkNum + 1.0) / numLines)
        {
            return;
        }
    }

}

bool getLink(const char* srcAddr, char* link, const int maxLinkLength)
{

    // shouldn't this be a size_t? or do variable length arrays need ints or something?
    const int bufSize = 1000;
    char buffer[bufSize]; 

   

    // equivalent to curl -s srcAddr | python3 getLinks.py | our_code
    FILE *pipe = getPipe(srcAddr, buffer, "getLinks", bufSize);
    // curl -s apparently spits out raw html of a page, so I assume the python file uses some html parser just to
    // get the text content. Apparently Beautiful soup is an html parser, so that makes sense...
    // this doesn't feel like a particularly 'c' way to do things, though.
    // I imagine much simpler than the alternative, though.


    // the first thing we expect the script to return is the number of links it found.
    int numLinks = 0;
    fscanf(pipe, "%d\n", &numLinks);

    //printf("LINKS: %d", numLinks); // <- I think this was here originally? maybe it was me at some point though, not sure.

    // the original code had the if inverted and the entire rest of the function was wrapped in it
    // that's kinda a smell to me so I reversed it.
    if(numLinks<=0)
    {
        pclose(pipe);
        return false;
    }

    getRandomLine(buffer, bufSize, pipe, numLinks);
   

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';

    /* get rid of the newline */
    char* pNewline = strchr(link, '\n');
    if(pNewline != NULL)
    {
        *pNewline = '\0';
    }

 
    return true;
 
}



int getText(const char* srcAddr, char* buffer, const int bufSize)
{
    // we look to be using the buffer twice, first for the command and then the actual bytes we read.
    // I guess popen doesn't read the buffer after it's called?
    // well, that does make sense.
    FILE *pipe = getPipe(srcAddr, buffer, "getText", bufSize);

    int bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
    buffer[bytesRead] = '\0';

    pclose(pipe);

    return bytesRead;
}
