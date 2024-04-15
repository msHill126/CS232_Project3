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


listElement* getIDFs(listElement* pageList, listElement* termList)
{
    listElement* idfList = NULL;
    for(int i = 0; i<getCount(termList); i++)
    {
        char* term = (char*)(getElementAt(termList, i)->obj);

        double* idf = malloc(sizeof(double));
        if(idf == NULL)
        {
            fprintf(stderr, "malloc failed in getIDFs.\n");
            exit(1);
        }
        
        *idf = calcIDF(pageList, term);

        if(!addElement(&idfList, doublefloat, idf))
        {
            fprintf(stderr, "addElement fialed in getIDFs.\n");
            exit(1);
        }
    }

    return idfList;
}



double score(indexedPage* page, listElement* termList, listElement* idfList)
{
    size_t numTerms = getCount(termList);
    double score = 0.0;
    for(int i = 0; i<numTerms; i++)
    {
        char* term = (char*)(getElementAt(termList, i)->obj);

        score+=scoreTerm(page, term, *(double*)(getElementAt(idfList, i)->obj));
    }

    return score;
}