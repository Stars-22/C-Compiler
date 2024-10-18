#include "LexicalAnalyzerGenerator.h"
#include <iostream>
#include <string>
#include <cctype>  // �����ַ���⺯���� isalpha, isdigit
#include <unordered_map>
#include "syn.h"

// ���캯������ʼ���ʷ�������
LexicalAnalyzerGenerator::LexicalAnalyzerGenerator(std::string cppfile) : file(cppfile) {
	analyze();  // ���÷����������з���
}

// ����������ɨ�貢��������Ĵ����ļ�
void LexicalAnalyzerGenerator::analyze() {
	size_t pos = 0;  // ��ǰ����λ��

	// ����Ԥ����ָ��� #include �� #define
	while (pos < file.length()) {
		if (isspace(file[pos])) {  // �����հ��ַ�
			pos++;
			continue;
		}
		if (file[pos] == '#') {  // ����Ԥ����ָ��� #include, #define ��
			std::string directive = readDirective(pos);
			std::cout << "Ԥ����ָ��: " << directive << std::endl;
			// ����չ������ handlePreprocessorDirective(directive);
			continue;
		}
		break;
	}

	// ��ʷ��������ļ�
	while (pos < file.length()) {
		int status = 0;  // ��ʼ��״̬��
		std::string word = splitword(pos, status);  // ��ȡ��ǰ��

		// ����״̬����ʻ����Ͳ����
		if (status == 100) {
			for (int i = KeywordNumStart; i <= KeywordNumEnd; i++) {
				if (strcmp(word.c_str(), SynCoding[i]) == 0) {
					status = i;
					std::cout << "�ؼ��֣�(" << word << ", " << status << ")" << std::endl;
					break;
				}
			}
		}
		if (status >= OperatorNumStart && status <= OperatorNumEnd) {
			std::cout << "�������(" << word << ", " << status << ")" << std::endl;
		}
		if (status >= DelimiterNumStart && status <= DelimiterNumEnd) {
			std::cout << " ��� ��(" << word << ", " << status << ")" << std::endl;
		}
		if (status == 100) {
			status = 401;
			std::cout << "��ʶ����(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 407) {
			status = 402;
			std::cout << " �ַ� ��(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 410) {
			status = 403;
			std::cout << "�ַ�����(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 403) {
			status = 404;
			std::cout << " ���� ��(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 401) {
			status = 404;
			std::cout << " ���� ��(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 404) {
			status = 404;
			int num_10 = std::stoi(word, nullptr, 8);
			std::cout << " ���� ��(" << word << ", " << status << ")" << "(" << num_10 << "�İ˽��Ʊ�ʾ��ʽ)" << std::endl;
			continue;
		}
		if (status == 406) {
			status = 404;
			int num_10 = std::stoi(word, nullptr, 16);
			std::cout << " ���� ��(" << word << ", " << status << ")" << "(" << num_10 << "��ʮ�����Ʊ�ʾ��ʽ)" << std::endl;
			continue;
		}
		if (status == 413) {
			status = 405;
			std::cout << " ʵ�� ��(" << word << ", " << status << ")" << std::endl;
			continue;
		}
		if (status == 0) {
			return;
		}
	}
}

// �ָ�ʻ㣺����״̬ת����ȡ��ǰ��
std::string LexicalAnalyzerGenerator::splitword(size_t& p, int& status) {
	size_t start = 0;
	int temp = 0;

	while ((temp = statusConversion(status, p)) != -1 && p < file.length()) {
		if (status == 0 && temp != 0) {
			start = p;  // ��¼�ʵ���ʼλ��
		}
		status = temp;
		p++;
	}
	if (p == file.length()) p--;
	if (start >= p) return "";
	return file.substr(start, p - start);  // ���شʻ�
}

// ��ȡԤ����ָ��
std::string LexicalAnalyzerGenerator::readDirective(size_t& p) {
	size_t start = p;
	while (p < file.length() && file[p] != '\n') {
		p++;  // ��ȡֱ�����з�
	}
	return file.substr(start, p - start);  // ����ָ��
}

// ����Ԥ����ָ��
void LexicalAnalyzerGenerator::handlePreprocessorDirective(const std::string& directive) {
	if (directive.find("#include") != std::string::npos) {
		std::cout << "���� #include ָ��: " << directive << std::endl;
	}
	else if (directive.find("#define") != std::string::npos) {
		std::cout << "���� #define ָ��: " << directive << std::endl;
	}
	else {
		std::cout << "��������Ԥ����ָ��: " << directive << std::endl;
	}
}

// �ַ��Ƚϣ��ж��ַ��Ƿ��ڸ�����Χ��
bool LexicalAnalyzerGenerator::compare(char c, char start, char end) {
	if (c >= start && c <= end) return true;
	else return false;
}

// ״̬ת�����������ݵ�ǰ�ַ���״̬����״̬ת��
int LexicalAnalyzerGenerator::statusConversion(int status, size_t& p)
{
	// �ַ�����ֵ���ؼ��ּ��
	if (status == 0) {
		if (compare(file[p], '1', '9')) {
			return 401;  // ʮ������ֵ
		}
		if (file[p] == '0') {
			return 403;  // �˽���/ʮ��������ֵ
		}
		if (file[p] == '\'') {
			return 407;  // �ַ�������
		}
		if (file[p] == '\"') {
			return 410;  // �ַ���������
		}
		if (compare(file[p], 'A', 'Z') || compare(file[p], 'a', 'z') || file[p] == '_') {
			return 100;  // ��ʶ����ؼ���
		}
	}
	if (status == 401) {  // ����ʮ������ֵ
		if (file[p] == '.') {
			return 413;  // ʵ��
		}
		if (!compare(file[p], '0', '9')) {
			return -1;
		}
	}
	if (status == 413) {  // ����ʵ��
		if (!compare(file[p], '0', '9')) {
			return -1;
		}
	}
	if (status == 403) {  // ����˽���/ʮ��������ֵ
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
	if (status == 404) {  // ����˽�����ֵ
		if (!compare(file[p], '0', '7')) {
			return -1;
		}
	}
	if (status == 405) {  // ����ʮ��������ֵ
		if (compare(file[p], '0', '9') || compare(file[p], 'a', 'f') || compare(file[p], 'A', 'F')) {
			return 406;
		}
		else {
			return -1;
		}
	}
	if (status == 406) {// ����ʮ��������ֵ
		if (!(compare(file[p], '0', '9') || compare(file[p], 'a', 'f') || compare(file[p], 'A', 'F'))) {
			return -1;
		}
	}
	if (status == 407) {  // �����ַ�������
		if (file[p] == '\'') {
			p++;
			return -1;
		}
	}
	if (status == 410) {  // �����ַ���������
		if (file[p] == '\"') {
			p++;
			return -1;
		}
	}
	if (status == 100) {  // ����ؼ��ֻ��ʶ��
		if (!(compare(file[p], 'A', 'Z') || compare(file[p], 'a', 'z') || file[p] == '_' || compare(file[p], '0', '9'))) {
			return -1;
		}
	}

	//�����������
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
	
	return status;  // ����ԭ״̬
}