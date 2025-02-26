#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional> // �� std::function
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text, sf::Font& font);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);
    void setText(const std::string& text);
    void setColor(sf::Color buttonColor, sf::Color textColor);

    void startCountdown(int seconds);  // �ѧ��ѹ������Ѻ�����ѧ
    bool isCountdownFinished() const;  // ��Ǩ�ͺ���������������ѧ

    void setOnCountdownFinish(std::function<void()> callback); // �ѧ��ѹ��駤����ѧ�ҡ�Ѻ�����ѧ����

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    void centerText();

    sf::Clock countdownClock; // ���ԡ�����Ѻ�Ѻ���Ҷ����ѧ
    int countdownDuration = 0;  // ������Ǣͧ��ùѺ�����ѧ (�Թҷ�)
    bool countdownActive = false; // ������鹻Դ��ùѺ�����ѧ

    std::function<void()> onCountdownFinish = nullptr; // Callback function
};

#endif
