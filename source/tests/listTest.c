#include "../collection/collection.h"
#include <string.h>
#include "test.h"

bool basicComprehension(void)
{
    listElement* list = NULL;
    int* num = malloc(sizeof(int));
    *num = 15;
    if(!addElement(&list, integer, num)) return false;

    char* str = malloc(sizeof(char)*12);
    strncpy(str, "Hello!", 12);
    if(!addElement(&list, cstring, str)) return false;

    num = malloc(sizeof(int));
    *num = 45;
    if(!addElement(&list, integer, num)) return false;
    printf("\tsuccessfully added elements...\n");

    if(getCount(list)!=3)
    {
        printf("\tWrong size of '%ld'. Expected 3.\n", getCount(list));
        return false;
    }

    if(getElementIndex(list, num)!=2)
    {
        printf("\tExpected 45 to be the 2nd element.\n");
        return false;
    }

    printf("\tPrinting list:\n");
    printList(stdout, list);
    
    if(getElementAt(list, 0)==NULL) 
    {
        printf("\tunable to get 0th element.\n");
        return false;
    }

    if( getElementAt(list, 0)->t != integer)
    {
           printf("\t0th element was not an integer as expected.\n");
        return false;
    }

    int value =*((int*)(getElementAt(list, 0)->obj));
    if(value != 15)
    {
        printf("\t0th element was '%d', not 15 as expected.\n", value);
        return false;
    }


    if(getElementAt(list, 1)==NULL || getElementAt(list, 1)->t != cstring ||  strcmp("Hello!", (char*)(getElementAt(list, 1)->obj))!=0)
    {
        printf("\tunable to confirm second element.\n");
        return false;
    }

    if(getElementAt(list, 3)!=NULL)
    {
        printf("\tlist had too many elements?\n");
    }

    freeList(list);
    return true;
}


 
bool insertion(void)
{
    listElement* list = NULL;
    int* num = malloc(sizeof(int));
    *num = 5;
    if(!addElement(&list, integer, num)) return false;

    num = malloc(sizeof(int));
    *num = 15;
    if(!addElement(&list, integer, num)) return false;

    num = malloc(sizeof(int));
    *num = 25;
    if(!addElement(&list, integer, num)) return false;
    printf("\tsuccessfully added starting elements...\n");


    num = malloc(sizeof(int));
    *num = 0;
    if(!addElementAt(&list, integer, num, 0)) return false;
    num = malloc(sizeof(int));
    *num = 10;
    if(!addElementAt(&list, integer, num, 2)) return false;
    num = malloc(sizeof(int));
    *num = 20;
    if(!addElementAt(&list, integer, num, 4)) return false;
    printf("\tsuccessfully inserted elements...\n");

    printList(stdout, list);
    if(!checkInt(getCount(list),6)) return false;
    for(int i = 0; i<6; i++)
    {
        listElement* ele = getElementAt(list, i);
        if(!checkPointerNull(ele, false)) return false;
        int x = *(int*)(ele->obj);
        if(!checkInt(x,i*5)) return false;
    }

    freeList(list);
    return true;

}



bool deletion(void)
{
    listElement* list = NULL;
    int* num = malloc(sizeof(int));
    *num = 5;
    if(!addElement(&list, integer, num)) return false;

    num = malloc(sizeof(int));
    *num = 15;
    if(!addElement(&list, integer, num)) return false;

    num = malloc(sizeof(int));
    int* last = num;
    *num = 25;
    if(!addElement(&list, integer, num)) return false;
    printf("\tsuccessfully added starting elements...\n");


    num = malloc(sizeof(int));
    *num = 0;
    if(!addElementAt(&list, integer, num, 0)) return false;
    num = malloc(sizeof(int));
    *num = 10;
    if(!addElementAt(&list, integer, num, 2)) return false;
    num = malloc(sizeof(int));
    *num = 20;
    if(!addElementAt(&list, integer, num, 4)) return false;
    printf("\tsuccessfully inserted elements...\n");

    if(!removeElement(&list, last)) return false;
    printf("\tDeleted last element.\n");

    printList(stdout, list);
    if(!checkInt(getCount(list), 5)) return false;

    for(int i = 0; i<5; i++)
    {
        listElement* ele = getElementAt(list, i);
        if(!checkPointerNull(ele, false)) return false;
        int x = *(int*)(ele->obj);
        if(!checkInt(x,i*5)) return false;
    }


    if(!removeElementAt(&list, 0)) return false;
    printf("\tDeleted first element.\n");

    printList(stdout, list);
    if(!checkInt(getCount(list), 4)) return false;

    for(int i = 0; i<4; i++)
    {
        listElement* ele = getElementAt(list, i);
        if(!checkPointerNull(ele, false)) return false;
        int x = *(int*)(ele->obj);
        if(!checkInt(x,(i*5)+5)) return false;
    }

    freeList(list);
    return true;

}
