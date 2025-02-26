#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional> // ใช้ std::function
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text, sf::Font& font);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);
    void setText(const std::string& text);
    void setColor(sf::Color buttonColor, sf::Color textColor);

    void startCountdown(int seconds);  // ฟังก์ชันเริ่มนับถอยหลัง
    bool isCountdownFinished() const;  // ตรวจสอบว่าเวลาหมดหรือยัง

    void setOnCountdownFinish(std::function<void()> callback); // ฟังก์ชันตั้งค่าหลังจากนับถอยหลังเสร็จ

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    void centerText();

    sf::Clock countdownClock; // นาฬิกาสำหรับนับเวลาถอยหลัง
    int countdownDuration = 0;  // ความยาวของการนับถอยหลัง (วินาที)
    bool countdownActive = false; // เริ่มต้นปิดการนับถอยหลัง

    std::function<void()> onCountdownFinish = nullptr; // Callback function
};

#endif
