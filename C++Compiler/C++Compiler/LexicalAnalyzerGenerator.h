#pragma once
#include <string>
#include <iostream>

class LexicalAnalyzerGenerator
{
public:
    // 构造函数，接受输入文件内容
    LexicalAnalyzerGenerator(std::string cppfile);

    // 词法分析的主函数
    void analyze();

private:
    // 输入的 C++ 文件代码内容
    std::string file;

    // 读取预处理指令
    std::string readDirective(size_t& pos);

    // 处理预处理指令
    void handlePreprocessorDirective(const std::string& directive);

    //拆分单词
    std::string splitword(size_t& p, int& status);

    //状态转化
    int statusConversion(int status, size_t& p);

    //字符比较
    bool compare(char c, char start, char end);

};

