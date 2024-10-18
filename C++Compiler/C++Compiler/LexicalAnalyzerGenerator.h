#pragma once
#include <string>
#include <iostream>

class LexicalAnalyzerGenerator
{
public:
    // ���캯�������������ļ�����
    LexicalAnalyzerGenerator(std::string cppfile);

    // �ʷ�������������
    void analyze();

private:
    // ����� C++ �ļ���������
    std::string file;

    // ��ȡԤ����ָ��
    std::string readDirective(size_t& pos);

    // ����Ԥ����ָ��
    void handlePreprocessorDirective(const std::string& directive);

    //��ֵ���
    std::string splitword(size_t& p, int& status);

    //״̬ת��
    int statusConversion(int status, size_t& p);

    //�ַ��Ƚ�
    bool compare(char c, char start, char end);

};

