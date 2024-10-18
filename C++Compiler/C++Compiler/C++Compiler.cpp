#include <iostream>
#include <cstring>
#include "initialize.cpp"
#include "syn.cpp"
#include "LexicalAnalyzerGenerator.cpp"



int main(int argc, char* argv[]) {
	// initialize();
	// std::cout << argv[1] << std::endl;
	if (argc < 2) {
		help();
		std::cout << "Press Enter to exit...";
		std::cin.get(); // 等待用户按下Enter键  
		return 1;  // 提供参数不足时直接退出
	}
	// 如果参数为-syn，调用synPrint打印符号表
	if (strcmp(argv[1], "-syn") == 0) {
		synPrint();
	}
	// 如果参数为-lag，读取传入的C++代码文件并进行转换
	if (strcmp(argv[1], "-lag") == 0) {
		if (argc < 3) {
			std::cerr << "Please provide a file for Status Conversion" << std::endl;
			return 1;
		}
		std::string cppfile = codeRead(argv[2]);  // 读取代码文件
		if (!cppfile.empty()) {
			LexicalAnalyzerGenerator lag(cppfile);  // 自动调用 analyze() 进行词法分析
		}
	}

	return 0;
}
