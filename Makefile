GCCFlags = -g -Wall -std=c11
testOut = -o output/test
SourceFiles = source/collection/*
TestFiles = source/tests/test.c

listTest:
	rm -f output/*
	gcc $(GCCFlags) $(testOut) $(SourceFiles) $(TestFiles)
