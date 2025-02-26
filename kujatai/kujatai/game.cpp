#include "game.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>


void randMoney(std::vector<int>& playerMoney, std::vector<std::string>& playerMoneyChanges) {
    static bool isSeedSet = false;
    if (!isSeedSet) {
        srand(time(0));
        isSeedSet = true;
    }

    int amounts[] = { 1000, 2000, -1000, -2000, 5000, 3000, 4000, -2000, 4600, -3000, 5600, 4000, -3440, 1000 };
    int numAmounts = sizeof(amounts) / sizeof(amounts[0]);

    playerMoneyChanges.clear(); // ??????????????????????????????????

    for (size_t i = 0; i < playerMoney.size(); i++) {
        int change = amounts[rand() % numAmounts];
        playerMoney[i] += change;

        // ?????????????????????? std::cout
        playerMoneyChanges.push_back(
            "Player " + std::to_string(i + 1) +
            (change >= 0 ? " received: +" : " lost: ") +
            std::to_string(change) + " dollars | Balance: " +
            std::to_string(playerMoney[i]) + " dollars"
        );
    }
}

void drawPlayerTable(sf::RenderWindow& window,sf::Font font ,const std::vector<Player>& players,sf::Color color = sf::Color::White) {
    float startY = 50;  // �ش������� Y
    float startX = 50;  // �ش������� X
    float rowSpacing = 50; // ������ҧ�����ҧ��

    // Header �ͧ���ҧ
    sf::Text header;
    header.setFont(font);
    header.setCharacterSize(40);
    header.setFillColor(sf::Color::Yellow);
    header.setString("Player           Cash          Shares       Profit/Loss");
    header.setPosition(startX, startY);
    window.draw(header);

    // �ʴ������Ţͧ�����蹷ء��
    for (size_t i = 0; i < players.size(); ++i) {
        float yPos = startY + (i + 1) * rowSpacing; // �ӹǳ���˹� Y

        sf::Text playerText;
        playerText.setFont(font);
        playerText.setCharacterSize(30);
        playerText.setFillColor(color);

        // �� padding ������������������͹���ҧ
        std::string name = players[i].getName();
        std::string cash = std::to_string(players[i].getCash());
        std::string shares = std::to_string(players[i].getShares());
        std::string profitLoss = std::to_string(players[i].getProfitLoss());

        // �Ѵ��ͤ������������ٻẺ�������
        std::string formattedText = name + std::string(25 - name.length(), ' ') +
            cash + std::string(25 - cash.length(), ' ') +
            shares + std::string(25 - shares.length(), ' ') +
            profitLoss;

        playerText.setString(formattedText);
        playerText.setPosition(startX, yPos);
        window.draw(playerText);
    }
}
