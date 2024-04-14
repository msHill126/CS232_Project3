# include "integration/integration.h"

int main(int argc, char* argv[])
{

    listElement* pageList = part1(argc, argv);
    
    printList(stdout, pageList);
    freeList(pageList);
    return 0;
}