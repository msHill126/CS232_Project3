#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

testSuite* newSuite(char* name, unitTest* tests, size_t testCount)
{
    testSuite* toRet = malloc(sizeof(testSuite));
    if(toRet == NULL)
    {
        fprintf(stderr, "Could not create suite '%s'. Aborting.\n", name);
        exit(1);
    }

    toRet->name = name;
    toRet->tests = tests;
    toRet->testCount = testCount;
    return toRet;
}

void freeSuite(testSuite* toFree)
{
    for(int i = 0; i<toFree->testCount; i++)
    {
        free( &(toFree->tests[i]));
    }

    free(toFree);
}

bool checkInt(int val, int expected)
{
    if(val== expected)
    {
        return true;
    }

    printf("\tint was %d. Expected %d.\n", val, expected);
    return false;

}

bool checkStr(char* val, char* expected)
{
    if(!strcmp(val, expected))
    {
        return true;
    }

    printf("\tstring was '%s'. Expected '%s'.\n", val, expected);
    return false;
}

bool checkPointer(void* val, void* expected)
{
    if(val==expected)
    {
        return true;
    }

    printf("\tpointers were not equal.\n");
    return false;
}


bool checkPointerNull(void* val, bool shouldBeNull)
{
    if((val==NULL && shouldBeNull) || (val!=NULL && !shouldBeNull))
    {
        return true;
    }

    if(shouldBeNull)
    {
        printf("\tPointer was not null and should have been.\n");
    }
    else
    {
        printf("\t Pointer was null and should not have been.\n");
    }

    return false;
}



unitTest* newTest(char* name, bool(*test)())
{
    unitTest* t = malloc(sizeof(unitTest));
    if(t == NULL)
    {
        fprintf(stderr, "Could not create test '%s'. Aborting.\n", name);
        exit(1);
    }

    t->name = name;
    t->test = test;
    t->passed = false;

    return t;
}

bool run(unitTest* t)
{
    printf("Running test '%s'.\n", t->name);
    bool toRet = t->test();
    t->passed = toRet;
    if(toRet)
    {
        printf("PASS");
    }
    else
    {
        printf("FAIL");
    }

    printf(": test '%s'\n\n", t->name);

    return toRet;
}


int runSuite(testSuite* suite)
{
    int pass = 0;
    printf("----------%s-----------\n\n", suite->name);

    for(int i = 0; i<suite->testCount; i++)
    {
        if(run(&(suite->tests[i])))
        {
            pass++;
        }
      
    }

    printf("\nSuite '%s': %d/%ld passing.\n", suite->name, pass, suite->testCount);
    return pass;
}

