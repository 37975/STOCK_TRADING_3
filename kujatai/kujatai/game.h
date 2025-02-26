#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void randMoney(std::vector<int>& playerMoney, std::vector<std::string>& playerMoneyChanges);
void drawPlayerTable(sf::RenderWindow& window,sf::Font font, const std::vector<Player>& players,sf::Color color);

#endif
