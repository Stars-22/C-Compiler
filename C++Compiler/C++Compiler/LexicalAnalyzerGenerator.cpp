#include "LexicalAnalyzerGenerator.h"
#include <iostream>
#include <string>
#include <cctype>  // 用于字符检测函数如 isalpha, isdigit
#include <unordered_map>
#include "syn.h"

// 构造函数，初始化词法分析器
LexicalAnalyzerGenerator::LexicalAnalyzerGenerator(std::string cppfile) : file(cppfile) {
	analyze();  // 调用分析函数进行分析
}

// 分析函数：扫描并解析输入的代码文件
void LexicalAnalyzerGenerator::analyze() {
	size_t pos = 0;  // 当前分析位置

	// 处理预处理指令，如 #include 或 #define
	while (pos < file.length()) {
		if (isspace(file[pos])) {  // 跳过空白字符
			pos++;
			continue;
		}
		if (file[pos] == '#') {  // 处理预处理指令，如 #include, #define 等
			std::string directive = readDirective(pos);
			std::cout << "预处理指令: " << directive << std::endl;
			// 可扩展处理函数 handlePreprocessorDirective(directive);
			continue;
		}
		break;
	}

	// 逐词分析输入文件
	while (pos < file.length()) {
		int status = 0;  // 初始化状态码
		std::string word = splitword(pos, status);  // 获取当前词

		// 根据状态处理词汇类型并输出
		if (status == 100) {
			for (int i = KeywordNumStart; i <= KeywordNumEnd; i++) {
				if (strcmp(word.c_str(), SynCoding[i]) == 0) {
					status = i;
					std::cout << "关键字：(" << word << ", " << status << ")" << std::endl;
					break;
				}
			}
		}
		if (status >= OperatorNumStart && status <= OperatorNumEnd) {
			std::cout << "运算符：(" << word << ", " << status << ")" << std::endl;
		}
		if (status >= DelimiterNumStart && status <= DelimiterNumEnd) {
			std::cout << " 界符 ：(" << word << ", " << status << ")" << std::endl;
		}
		if (status == 100) {
			status = 401;
			std::cout << "标识符：(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 407) {
			status = 402;
			std::cout << " 字符 ：(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 410) {
			status = 403;
			std::cout << "字符串：(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 403) {
			status = 404;
			std::cout << " 整数 ：(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 401) {
			status = 404;
			std::cout << " 整数 ：(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 404) {
			status = 404;
			int num_10 = std::stoi(word, nullptr, 8);
			std::cout << " 整数 ：(" << word << ", " << status << ")" << "(" << num_10 << "的八进制表示形式)" << std::endl;
			continue;
		}
		if (status == 406) {
			status = 404;
			int num_10 = std::stoi(word, nullptr, 16);
			std::cout << " 整数 ：(" << word << ", " << status << ")" << "(" << num_10 << "的十六进制表示形式)" << std::endl;
			continue;
		}
		if (status == 413) {
			status = 405;
			std::cout << " 实数 ：(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 0) {
			return;
		}
	}
}

// 分割词汇：根据状态转换获取当前词
std::string LexicalAnalyzerGenerator::splitword(size_t& p, int& status) {
	size_t start = 0;
	int temp = 0;

	while ((temp = statusConversion(status, p)) != -1 && p < file.length()) {
		if (status == 0 && temp != 0) {
			start = p;  // 记录词的起始位置
		}
		status = temp;
		p++;
	}
	if (p == file.length()) p--;
	if (start >= p) return "";
	return file.substr(start, p - start);  // 返回词汇
}

// 读取预处理指令
std::string LexicalAnalyzerGenerator::readDirective(size_t& p) {
	size_t start = p;
	while (p < file.length() && file[p] != '\n') {
		p++;  // 读取直到换行符
	}
	return file.substr(start, p - start);  // 返回指令
}

// 处理预处理指令
void LexicalAnalyzerGenerator::handlePreprocessorDirective(const std::string& directive) {
	if (directive.find("#include") != std::string::npos) {
		std::cout << "处理 #include 指令: " << directive << std::endl;
	}
	else if (directive.find("#define") != std::string::npos) {
		std::cout << "处理 #define 指令: " << directive << std::endl;
	}
	else {
		std::cout << "处理其他预处理指令: " << directive << std::endl;
	}
}

// 字符比较：判断字符是否在给定范围内
bool LexicalAnalyzerGenerator::compare(char c, char start, char end) {
	if (c >= start && c <= end) return true;
	else return false;
}

// 状态转换函数：根据当前字符和状态进行状态转移
int LexicalAnalyzerGenerator::statusConversion(int status, size_t& p)
{
	// 字符、数值、关键字检测
	if (status == 0) {
		if (compare(file[p], '1', '9')) {
			return 401;  // 十进制数值
		}
		if (file[p] == '0') {
			return 403;  // 八进制/十六进制数值
		}
		if (file[p] == '\'') {
			return 407;  // 字符字面量
		}
		if (file[p] == '\"') {
			return 410;  // 字符串字面量
		}
		if (compare(file[p], 'A', 'Z') || compare(file[p], 'a', 'z') || file[p] == '_') {
			return 100;  // 标识符或关键字
		}
	}
	if (status == 401) {  // 处理十进制数值
		if (file[p] == '.') {
			return 413;  // 实数
		}
		if (!compare(file[p], '0', '9')) {
			return -1;
		}
	}
	if (status == 413) {  // 处理实数
		if (!compare(file[p], '0', '9')) {
			return -1;
		}
	}
	if (status == 403) {  // 处理八进制/十六进制数值
		if (file[p] == 'x' || file[p] == 'X') {
			return 405;
		}
		else if (compare(file[p], '0', '7')) {
			return 404;
		}
		else {
			return -1;
		}
	}
	if (status == 404) {  // 处理八进制数值
		if (!compare(file[p], '0', '7')) {
			return -1;
		}
	}
	if (status == 405) {  // 处理十六进制数值
		if (compare(file[p], '0', '9') || compare(file[p], 'a', 'f') || compare(file[p], 'A', 'F')) {
			return 406;
		}
		else {
			return -1;
		}
	}
	if (status == 406) {// 结束十六进制数值
		if (!(compare(file[p], '0', '9') || compare(file[p], 'a', 'f') || compare(file[p], 'A', 'F'))) {
			return -1;
		}
	}
	if (status == 407) {  // 处理字符字面量
		if (file[p] == '\'') {
			p++;
			return -1;
		}
	}
	if (status == 410) {  // 处理字符串字面量
		if (file[p] == '\"') {
			p++;
			return -1;
		}
	}
	if (status == 100) {  // 处理关键字或标识符
		if (!(compare(file[p], 'A', 'Z') || compare(file[p], 'a', 'z') || file[p] == '_' || compare(file[p], '0', '9'))) {
			return -1;
		}
	}

	//运算符界符检测
	if (status == 0) {
		switch (file[p]) {
		case '+': return 201;
		case '-': return 202;
		case '*': return 203;
		case '/': return 204;
		case '%': return 205;
		case '=': return 223;
		case '!': return 216;
		case '>': return 210;
		case '<': return 211;
		case '&': return 217;
		case '|': return 218;
		case '^': return 219;
		case '~': return 220;
		case '?': return 234;
		case ':': return 235;
		case '.': return 236;
		case '(': return 239;
		case ')': return 240;
		case '[': return 241;
		case ']': return 242;
		case '{': return 304;
		case '}': return 305;
		case ';': return 306;
		case ',': return 307;
		}
	}
	if (status == 201) {
		if (file[p] == '+') return 206;
		if (file[p] == '=') return 224;
		return -1;
	}
	if (status == 202) {
		if (file[p] == '-') return 207;
		if (file[p] == '=') return 225;
		if (file[p] == '>') return 237;
		return -1;
	}
	if (status == 203) {
		if (file[p] == '=') return 226;
		if (file[p] == '/') return 303;
		return -1;
	}
	if (status == 204) {
		if (file[p] == '=') return 227;
		if (file[p] == '/') return 301;
		if (file[p] == '*') return 302;
		return -1;
	}
	if (status == 205) {
		if (file[p] == '=') return 228;
		return -1;
	}
	if (status == 223) {
		if (file[p] == '=') return 208;
		return -1;
	}
	if (status == 216) {
		if (file[p] == '=') return 209;
		return -1;
	}
	if (status == 210) {
		if (file[p] == '=') return 212;
		if (file[p] == '>') return 222;
		return -1;
	}
	if (status == 211) {
		if (file[p] == '=') return 213;
		if (file[p] == '<') return 221;
		return -1;
	}
	if (status == 217) {
		if (file[p] == '&') return 214;
		if (file[p] == '=') return 229;
		return -1;
	}
	if (status == 218) {
		if (file[p] == '|') return 215;
		if (file[p] == '=') return 230;
		return -1;
	}
	if (status == 219) {
		if (file[p] == '=') return 231;
		return -1;
	}
	if (status == 235) {
		if (file[p] == ':') return 238;
		return -1;
	}
	if (status == 222) {
		if (file[p] == '=') return 233;
		return -1;
	}
	if (status == 221) {
		if (file[p] == '=') return 232;
		return -1;
	}
	if (status == 213) return -1;
	if (status == 220) return -1;
	if (status == 234) return -1;
	if (status == 236) return -1;
	if (status == 239) return -1;
	if (status == 240) return -1;
	if (status == 241) return -1;
	if (status == 242) return -1;
	if (status == 304) return -1;
	if (status == 305) return -1;
	if (status == 306) return -1;
	if (status == 307) return -1;
	if (status == 206) return -1;
	if (status == 224) return -1;
	if (status == 207) return -1;
	if (status == 225) return -1;
	if (status == 237) return -1;
	if (status == 226) return -1;
	if (status == 303) return -1;
	if (status == 227) return -1;
	if (status == 301) return -1;
	if (status == 302) return -1;
	if (status == 228) return -1;
	if (status == 208) return -1;
	if (status == 209) return -1;
	if (status == 212) return -1;
	if (status == 214) return -1;
	if (status == 229) return -1;
	if (status == 215) return -1;
	if (status == 230) return -1;
	if (status == 231) return -1;
	if (status == 238) return -1;
	if (status == 233) return -1;
	if (status == 232) return -1;
	
	return status;  // 返回原状态
}