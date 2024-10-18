#include "StatusConversion.h"

StatusConversion::StatusConversion(std::string cppfile, int p) : file(cppfile), p(p) {
	status = 0;
	int temp = 0;
	while ((temp = run(status)) != -1) {
		status = temp;
		p++;
	}
}
