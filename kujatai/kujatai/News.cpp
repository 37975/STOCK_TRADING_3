#include "News.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

// Constructor: โหลดข่าวจากไฟล์
News::News(const std::string& filePath) {
    std::ifstream file(filePath);  // ใช้ filePath ที่ได้รับมา
    if (!file) {
        std::cerr << "Error opening news file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string newsText;
        int effect;

        size_t lastSpace = line.find_last_of(' ');
        if (lastSpace != std::string::npos) {
            newsText = line.substr(0, lastSpace);
            effect = std::stoi(line.substr(lastSpace + 1));
            newsList.push_back({ newsText, effect });
        }
    }
    file.close();
}

// ฟังก์ชันสุ่มข่าว
std::string News::getRandomNews() {
    if (newsList.empty()) {
        return "No news available";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, newsList.size() - 1);
    return newsList[dist(gen)].first;
}

// ดึงค่าผลกระทบของข่าว
int News::getNewsEffect() {
    if (newsList.empty()) {
        return 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, newsList.size() - 1);
    return newsList[dist(gen)].second;
}
