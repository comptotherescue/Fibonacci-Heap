keywordcounter: keywordcounter.o
	g++  keywordcounter.o -o keywordcounter 

keywordcounter.o: keywordcounter.cpp
	g++ -c keywordcounter.cpp -std=c++11


target: dependencies
	action
