#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int comp = 1;
	for (int i = 1; i < argc; i++)
		comp *= atoi(argv[i]);
	return comp;
}