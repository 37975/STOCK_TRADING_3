#pragma once
#ifndef NEWS_H
#define NEWS_H

#include <string>
#include <vector>

class News {
public:
    News(const std::string& filePath); // constructor ������Ŵ���Ǩҡ���
    std::string getRandomNews(); // �ѧ��ѹ������������
    int getNewsEffect(); // �ѧ��ѹ���ʹ֧�š�з��ҡ����

private:
    std::vector<std::pair<std::string, int>> newsList; // ������мš�з�
};

#endif
