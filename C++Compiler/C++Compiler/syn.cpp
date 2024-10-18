#include "syn.h"
#include <iostream>

static void synPrint() {
	std::cout << "关键字：" << std::endl;
	for (int i = KeywordNumStart; i <= KeywordNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
	std::cout << "运算符：" << std::endl;
	for (int i = OperatorNumStart; i <= OperatorNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
	std::cout << "界符：" << std::endl;
	for (int i = DelimiterNumStart; i <= DelimiterNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
	std::cout << "单词类别：" << std::endl;
	for (int i = WordTypeNumStart; i <= WordTypeNumEnd; i++) {
		std::cout << i << " -> " << SynCoding[i] << std::endl;
	}
}