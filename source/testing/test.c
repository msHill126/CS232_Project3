#include "tests/listTest.c"
#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool alwaysPass(void){return true;}
bool alwaysFail(void){return false;}

void runSuiteAndCalc(testSuite* suite, int* suites, int* tests, int* testsPassing)
{
    (*suites)++;
    *tests+=suite->testCount;
    *testsPassing += runSuite(suite);
}


int main(void)
{
    // this definitely feels like a crude imitation of real software...
    // I could make a suite struct, that would probably help.
  
    // eh, only way I could make this feel real would be to process the test files to generate this main method
    // that's a lot of effort.
    // unlike this which is only a moderate amount of effort.

    int suites = 0;
    int tests = 0;
    int testsPassing = 0;

    
    unitTest basicTests[] = { *newTest("Always Pass", &alwaysPass), *newTest("Always Fail", &alwaysFail)
    };

    runSuiteAndCalc(newSuite("Test Tests", basicTests, sizeof(basicTests)/sizeof(unitTest)), 
        &suites, &tests, &testsPassing);

    
    unitTest listTests[] = { *newTest("Basic Comprehension", &basicComprehension), *newTest("Insertion", &insertion),
        *newTest("Deletion", &deletion)
    };

    runSuiteAndCalc(  newSuite("List Tests", listTests, sizeof(listTests)/sizeof(unitTest)), 
        &suites, &tests, &testsPassing);
    
    printf("\n\n-------------RESULT-------------\n %d/%d tests from %d suites passing. See above for details.\n", testsPassing, tests, suites);

}