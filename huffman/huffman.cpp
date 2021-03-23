#include <iostream>
#include "huff.h"
bool CheckFiles(std::string file1, std::string file2)
{
	std::ifstream in1(file1);
	std::ifstream in2(file2);

	char a, b;
	in1.get(a);
	in2.get(b);
	while (!in1.eof() && !in2.eof())
	{
		if (a != b)
			return false;
		in1.get(a);
		in2.get(b);
	}

	if (in1.eof() && in2.eof())
		return true;

	return false;
}
int main()
{
	
	HTree test;
	if (test.code("source.txt", "coded.txt"))
	{
		test.decode("coded.txt", "decoded.txt");
		if (CheckFiles("source.txt", "decoded.txt"))
			std::cout << "right solution\n";
		else
			std::cout << "wrong solution\n";
	}
	
	return 0;

}

