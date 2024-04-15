# include "integration/integration.h"

int main(int argc, char* argv[])
{

    listElement* pageList = part1(argc, argv);
    
    part2(pageList);
    freeList(pageList);
    return 0;
}