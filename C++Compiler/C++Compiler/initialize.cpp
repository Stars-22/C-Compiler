#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

static std::string codeRead(const char* filename) {
    std::ifstream file(filename); // 替换为你的文件名
    std::string code;

    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        code = buffer.str();
        file.close();
    }
    else {
        std::cerr << "Unable to open codeFile";
        return "";
    }
    return code;
}

static void help() {
    std::cout << "Usage: program_name [-syn | -lag <filename>]" << std::endl;
    std::cout << "-syn: Print the list of keywords, operators, delimiters, and word categories." << std::endl;
    std::cout << "-lag <filename>: Perform lexical analysis on the specified C++ source file." << std::endl;
}