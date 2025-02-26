#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Button {
public:
    Button() : visible(true) {} // ปุ่มเริ่มต้นมองเห็น

    Button(string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor)
        : visible(true) { // ปุ่มมองเห็นเริ่มต้น
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::Black);
    }

    void setFont(sf::Font& font) {
        text.setFont(font);
    }

    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos);
        text.setPosition(pos.x + 10, pos.y + 10);
    }

    void setText(const string& t) {
        text.setString(t);
    }

    void hide() { visible = false; } // ซ่อนปุ่ม
    void show() { visible = true; }  // แสดงปุ่ม
    bool isVisible() { return visible; } // ตรวจสอบปุ่ม

    void drawTo(sf::RenderWindow& window) {
        if (visible) { // วาดเฉพาะเมื่อปุ่มมองเห็น
            window.draw(button);
            window.draw(text);
        }
    }

    bool isMouseOver(sf::RenderWindow& window) {
        if (!visible) return false; // ถ้าปุ่มซ่อน ให้เมาส์ไม่ทำงานกับปุ่ม
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect btnBounds = button.getGlobalBounds();
        return btnBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

private:
    sf::RectangleShape button;
    sf::Text text;
    bool visible; // ตัวแปรสถานะว่าปุ่มถูกซ่อนหรือไม่
};