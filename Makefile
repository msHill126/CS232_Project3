GCCFlags = -g -Wall 
testOut = -o output/test
out = -o output/webSearch
SourceFiles = source/collection/*.c source/crawling/*.c source/soup/*.c source/integration/*.c
TestFiles = source/testing/test.c source/testing/framework.c
MainFiles = source/main.c

main:
	rm -f output/*
	cp etc/* output
	gcc $(GCCFlags) $(out) $(SourceFiles) $(MainFiles)

tests:
	rm -f output/*
	gcc $(GCCFlags) $(testOut) $(SourceFiles) $(TestFiles)
