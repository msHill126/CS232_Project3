#include "crawl.h"
#include <math.h>

// honestly, this part seems pretty easy.

static double scoreTerm(indexedPage* page, char* term, double IDF)
{
    // not entirely sure how division type gets decided, so I made extra sure.
    double tf =  ((double)(getNode(term, page->root)->visits))/((double)page->termCount);
    return tf*IDF;
}


// doing this every time for every indexed page is probably a lot slower than it needs to be.
// oh well, nobody said it had to work well.
// the alternative was regeristing doubles with the listElement structure and calculating them before calculating scores,
// but that sounded annoying and I was lazy.
static double calcIDF(listElement* pageList, char* term)
{
    int numContaining = 0;
    for(int i = 0; i<getCount(pageList); i++)
    {
        indexedPage* page = getElementAt(pageList, i)->obj;
        if(getNode(term, page->root)!=NULL)
        {
            numContaining++;
        }
    }

    return log((1.0+getCount(pageList))/(1.0+numContaining));
}



double score(indexedPage* page, listElement* pageList, listElement* termList )
{
    size_t numTerms = getCount(termList);
    double score = 0.0;
    for(int i = 0; i<numTerms; i++)
    {
        char* term = (char*)(getElementAt(termList, i)->obj);

        score+=scoreTerm(page, term, calcIDF(pageList, term));
    }

    return score;
}