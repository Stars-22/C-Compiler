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
		std::cin.get(); // �ȴ��û�����Enter��  
		return 1;  // �ṩ��������ʱֱ���˳�
	}
	// �������Ϊ-syn������synPrint��ӡ���ű�
	if (strcmp(argv[1], "-syn") == 0) {
		synPrint();
	}
	// �������Ϊ-lag����ȡ�����C++�����ļ�������ת��
	if (strcmp(argv[1], "-lag") == 0) {
		if (argc < 3) {
			std::cerr << "Please provide a file for Status Conversion" << std::endl;
			return 1;
		}
		std::string cppfile = codeRead(argv[2]);  // ��ȡ�����ļ�
		if (!cppfile.empty()) {
			LexicalAnalyzerGenerator lag(cppfile);  // �Զ����� analyze() ���дʷ�����
		}
	}

	return 0;
}
