#include "Button.h"

// Constructor
Button::Button(float x, float y, float width, float height, const std::string& text, sf::Font& font) {
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setPosition(x, y);
    buttonShape.setFillColor(sf::Color::White);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::Black);

    centerText();
}

// ฟังก์ชันวาดปุ่ม
void Button::draw(sf::RenderWindow& window) {
    if (countdownActive) {
        int timeLeft = countdownDuration - countdownClock.getElapsedTime().asSeconds();
        if (timeLeft <= 0) {
            countdownActive = false;
            buttonText.setString("Next"); // กลับเป็นปุ่มปกติเมื่อหมดเวลา
            centerText();

            // ถ้ามีฟังก์ชันกำหนดให้ทำงานเมื่อหมดเวลา ก็เรียกใช้งาน
            if (onCountdownFinish) {
                onCountdownFinish();
            }
        }
        else {
            buttonText.setString("Next in " + std::to_string(timeLeft) + "s");
            centerText();
        }
    }

    window.draw(buttonShape);
    window.draw(buttonText);
}

// ตรวจสอบว่าปุ่มถูกคลิกหรือไม่
bool Button::isClicked(sf::Vector2i mousePos) {
    return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

// เปลี่ยนสีของปุ่มและตัวหนังสือ
void Button::setColor(sf::Color buttonColor, sf::Color textColor) {
    buttonShape.setFillColor(buttonColor);
    buttonText.setFillColor(textColor);
}

// ฟังก์ชันเริ่มต้นการนับถอยหลัง
void Button::startCountdown(int seconds) {
    countdownDuration = seconds;
    countdownClock.restart();  // รีเซ็ตนาฬิกา
    countdownActive = true;    // เปิดการนับถอยหลัง
}

// ตรวจสอบว่าเวลาหมดหรือยัง
bool Button::isCountdownFinished() const {
    return countdownActive && countdownClock.getElapsedTime().asSeconds() >= countdownDuration;
}

// ฟังก์ชันตั้งค่าฟังก์ชันที่ต้องเรียกใช้เมื่อหมดเวลา
void Button::setOnCountdownFinish(std::function<void()> callback) {
    onCountdownFinish = callback;
}

// ฟังก์ชันช่วยจัดตำแหน่งข้อความให้อยู่กึ่งกลางปุ่ม
void Button::centerText() {
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getSize().x - textBounds.width) / 2 - textBounds.left,
        buttonShape.getPosition().y + (buttonShape.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}
