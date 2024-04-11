#include <stdbool.h>
#ifndef TEST_H
#define TEST_H


struct unitTest
{
    // I know these things aren't actually unit tests because I use them to test like
    // 5 things at once, but I don't have the patience to do it properly, so meh.
    // test seemed like too generic of a name

    // also, obviously actual testing frameworks must exist, so this is pretty pointless, but sue me, I felt like it.
    char* name;
    bool (*test)();
    bool passed;
};

typedef struct unitTest unitTest;

unitTest* newTest(char* name, bool(*test)());

bool run(unitTest* t);

bool checkInt(int val, int expected);

bool checkStr(char* val, char* expected);

bool checkPointer(void* val, void* expected);

bool checkPointerNull(void* val, bool shouldBeNull);

#endif