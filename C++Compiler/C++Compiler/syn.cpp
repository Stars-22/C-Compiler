#include "syn.h"
#include <iostream>

static void synPrint() {
	std::cout << "�ؼ��֣�" << std::endl;
	for (int i = KeywordNumStart; i <= KeywordNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
	std::cout << "�������" << std::endl;
	for (int i = OperatorNumStart; i <= OperatorNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
	std::cout << "�����" << std::endl;
	for (int i = DelimiterNumStart; i <= DelimiterNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
	std::cout << "�������" << std::endl;
	for (int i = WordTypeNumStart; i <= WordTypeNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
}