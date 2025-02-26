#pragma once
#ifndef NEWS_H
#define NEWS_H

#include <string>
#include <vector>

class News {
public:
    News(const std::string& filePath); // constructor เพื่อโหลดข่าวจากไฟล์
    std::string getRandomNews(); // ฟังก์ชันเพื่อสุ่มข่าว
    int getNewsEffect(); // ฟังก์ชันเพื่อดึงผลกระทบจากข่าว

private:
    std::vector<std::pair<std::string, int>> newsList; // ข่าวและผลกระทบ
};

#endif
