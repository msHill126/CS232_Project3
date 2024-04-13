GCCFlags = -g -Wall -std=c11
testOut = -o output/test
SourceFiles = source/collection/*.c source/crawling/*.c source/soup/*.c
TestFiles = source/testing/test.c source/testing/framework.c
MainFiles = source/testmain.c

main:
	rm -f output/*
	cp etc/* output
	gcc $(GCCFlags) $(testOut) $(SourceFiles) $(MainFiles)

tests:
	rm -f output/*
	gcc $(GCCFlags) $(testOut) $(SourceFiles) $(TestFiles)
