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

// �ѧ��ѹ�Ҵ����
void Button::draw(sf::RenderWindow& window) {
    if (countdownActive) {
        int timeLeft = countdownDuration - countdownClock.getElapsedTime().asSeconds();
        if (timeLeft <= 0) {
            countdownActive = false;
            buttonText.setString("Next"); // ��Ѻ�繻�������������������
            centerText();

            // ����տѧ��ѹ��˹����ӧҹ������������ �����¡��ҹ
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

// ��Ǩ�ͺ��һ����١��ԡ�������
bool Button::isClicked(sf::Vector2i mousePos) {
    return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

// ����¹�բͧ������е��˹ѧ���
void Button::setColor(sf::Color buttonColor, sf::Color textColor) {
    buttonShape.setFillColor(buttonColor);
    buttonText.setFillColor(textColor);
}

// �ѧ��ѹ������鹡�ùѺ�����ѧ
void Button::startCountdown(int seconds) {
    countdownDuration = seconds;
    countdownClock.restart();  // ���絹��ԡ�
    countdownActive = true;    // �Դ��ùѺ�����ѧ
}

// ��Ǩ�ͺ���������������ѧ
bool Button::isCountdownFinished() const {
    return countdownActive && countdownClock.getElapsedTime().asSeconds() >= countdownDuration;
}

// �ѧ��ѹ��駤�ҿѧ��ѹ����ͧ���¡��������������
void Button::setOnCountdownFinish(std::function<void()> callback) {
    onCountdownFinish = callback;
}

// �ѧ��ѹ���¨Ѵ���˹觢�ͤ�����������觡�ҧ����
void Button::centerText() {
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getSize().x - textBounds.width) / 2 - textBounds.left,
        buttonShape.getPosition().y + (buttonShape.getSize().y - textBounds.height) / 2 - textBounds.top
    );
}
