#include "test.h"
#include "listTest.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static bool runTestTests = true;
static bool runListTests = true;

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


int runSuite(char* name, unitTest* tests, size_t count)
{
    int pass = 0;
    printf("----------%s-----------\n\n", name);

    for(int i = 0; i<count; i++)
    {
        if(run(&tests[i]))
        {
            pass++;
        }
      
    }

    printf("\nSuite '%s': %d/%ld passing.\n", name, pass, count);
    return pass;
}


bool alwaysPass(void){return true;}
bool alwaysFail(void){return false;}


int main(void)
{
    // this definitely feels like a crude imitation of real software...
    // I could make a suite struct, that would probably help.

    unitTest basicTests[] = { *newTest("Always Pass", &alwaysPass), *newTest("Always Fail", &alwaysFail)
    };
    size_t basicTestsCount = sizeof(basicTests)/sizeof(unitTest);
    unitTest listTests[] = { *newTest("Basic Comprehension", &basicComprehension), *newTest("Insertion", &insertion),
        *newTest("Deletion", &deletion)
    };
    size_t listTestsCount = sizeof(listTests)/sizeof(unitTest);


    int suites = 0;
    int tests = 0;
    int testsPassing = 0;

    if(runTestTests)
    {
        suites++;
        tests+=basicTestsCount;

        testsPassing += runSuite("Test Tests", basicTests, basicTestsCount);
    }


    if(runListTests)
    {
        suites++;
        tests+=listTestsCount;

        testsPassing += runSuite("List Tests", listTests, listTestsCount);
    }

    
    printf("\n\n-------------RESULT-------------\n %d/%d tests from %d suites passing. See above for details.\n", testsPassing, tests, suites);

}