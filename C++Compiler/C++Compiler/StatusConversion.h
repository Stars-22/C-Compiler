#pragma once
#include <string>

class StatusConversion {
public:
	StatusConversion(std::string cppfile, int p);
private:
	std::string file;
	int p;
	int status;
	int run(int status);
	bool compare(char c, char start, char end);
};

