#include <stdio.h>
#include <stdlib.h>
#include "StringBuffer.h"

int main(int argc, char **argv) {
	StringBuffer s1("Hello");
	StringBuffer s2("world!");
	s1.append(" ");
	s1.append(s2);

	//Hello	world!
	puts(s1.c_str());

	s1.set("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
	s1.append("\n");

	//124
	printf("%zu\n", s1.size());

	s2.clear();
	for	(int i = 0;	i < 10;	i++) {
		s2.insert(s1, 0);
	}
	//Lorem	ipsum ... 10 volte
	puts(s2.c_str());

	//1240
	printf("%zu\n", s2.size());

	return 0;
}