#include "crawl.h"
#include "../soup/soup.h"
#include "../collection/trie.h"
#include <string.h>


static const char* invalidChars =  " \t\n\r.,;:!?'\"()[]{}_-0123456789";
// thanks Tyler!
// actually this function is kinda long.
// Okay, refactoring time


static void fillTrie(char* buffer, trieNode* root)
{
    // Analyze the content and add words to the trie
    // this function isn't pretty but whatever.
   
    // a cursed for loop if I've ever seen one.
    for (char* word = strtok(buffer,invalidChars); word != NULL; word = strtok(NULL, invalidChars)) 
    {
        // Clean the word and convert it to lowercase
        char* cleanWord = malloc(strlen(word) + 1);
       
        if (cleanWord == NULL) 
        {
            fprintf(stderr, "Memory allocation failed for cleanWord\n");
            freeNode(root); // Free allocated memory before returning
            exit(1);
        }

        int j = 0;
        for (int i = 0; word[i] != '\0'; i++) 
        {
            if (isalpha(word[i])) 
            {
                cleanWord[j++] = tolower(word[i]);
            }
        }
        cleanWord[j] = '\0';

        printf("\t%s\n", cleanWord);

        visitNode(cleanWord, root);
        free(cleanWord);
       
    }

}


static trieNode* getTermFrequency(char* url) 
{

    printf("%s\n", url);
    // Store only first 300000 char 
    char buffer[300001]; // +1 for null terminator

    // check for text
    int bytesRead = getText(url, buffer, sizeof(buffer));
    if (bytesRead <= 0) 
    {
        fprintf(stderr, "Failed to retrieve text from URL: %s\n", url);
        return NULL; // Return NULL to indicate failure
    }

    trieNode* root = newTrie();

    fillTrie(buffer, root);

    return root; // Return the root node of the trie
}


static indexedPage* newPage(char* url, trieNode* frequency, int termCount)
{

    indexedPage* page = malloc(sizeof(indexedPage));
    if(page==NULL)
    {
        fprintf(stderr, "Malloc failed in newPage.");
        exit(1);
    
    }

    page->url = malloc(sizeof(char)*(strlen(url)+1));

    if(page->url == NULL)
    {
        fprintf(stderr, "Malloc failed in newPage.");
        free(page);
        exit(1);
    }

    strncpy(page->url, url, strlen(url)+1);

    page->root=frequency;
    page->termCount = termCount;
    return page;

}

static int termCount(trieNode* freq)
{
    if(freq == NULL) return 0;
    
    int toRet = 0;
    for(int i = 0; i<children_count; i++)
    {
        toRet+=termCount(freq->children[i]);
    }
    toRet+=freq->visits;
    return toRet;
}



indexedPage* indexPage(char* url)
{
    trieNode* freq = getTermFrequency(url);
    
    // now get total term count.
    int terms = termCount(freq);

    return newPage(url, freq, terms);

}


