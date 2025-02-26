#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Menu.h"
#include "TextBox.h"
#include "Button.h"
#include "News.h"
#include "game.h"
#include "gP_2.h"

void endTurn(int& , int& , int& ,int , bool& ,bool& , bool& ,Button& );

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "Stock Trading Game");

    Menu menu(window.getSize().x, window.getSize().y);

    // Load background images
    sf::Texture texture;
    if (!texture.loadFromFile("mon.png")) {
        std::cerr << "Error loading mon.png\n";
    }
    sf::Sprite background(texture);

    sf::Texture tot;
    if (!tot.loadFromFile("tuto.png")) {
        std::cerr << "Error loading tuto.png\n";
    }
    sf::Sprite top(tot);

    sf::Texture kornpl;
    if (!kornpl.loadFromFile("BGja.JPEG")) {
        std::cerr << "Error loading BGja.JPEG\n";
    }
    sf::Sprite kornplays(kornpl);

    sf::Texture start;
    if (!start.loadFromFile("startska.JPG")) {
        std::cerr << "Error loading startska.JPG\n";
    }
    sf::Sprite startja(start);

    // Create graph for StockGraph
    StockGraph stockGraph(800, 400);
    sf::RectangleShape graphArea(sf::Vector2f(800, 400));
    graphArea.setPosition(140, 150);
    graphArea.setFillColor(sf::Color::Black);

    // Choice menu texture
    sf::Texture choice;
    if (!choice.loadFromFile("choice.JPG")) {
        std::cerr << "Error loading choice.JPG\n";
    }
    sf::Sprite choicenaka(choice);

    bool inTutorial = false;
    bool isChoosingPlayers = false;
    bool isEnteringNames = false;
    bool isInStartScreen = false;
    bool isInGraphScreen = false;
    bool isInChoiceScreen = false;  // New state for choice screen

    bool menuVisible = true;  // Show menu initially

    int numberOfPlayers = 0;
    std::vector<TextBox> playerNameBoxes;

    sf::Font font;
    if (!font.loadFromFile("Rainbow Memories.otf")) {
        std::cerr << "Error loading font\n";
    }

    News news("C:/Users/Acer/source/repos/kujatai/news/news.txt");

    sf::Text newsText;
    newsText.setFont(font);
    newsText.setCharacterSize(40);
    newsText.setFillColor(sf::Color::White);
    newsText.setOutlineColor(sf::Color::Black);
    newsText.setOutlineThickness(3);
    newsText.setPosition(50, 50); // ปรับตำแหน่งตามต้องการ


    Button nextButton(450, 600, 150, 50, "Next", font);
    Button countdownButton(450, 600, 150, 50, "Next in ", font);
    countdownButton.startCountdown(15);
    Button graphButton(450, 650, 150, 50, "Show Graph", font);
    Button proceedButton(450, 700, 150, 50, "Proceed", font);
    Button backButton(10, 10, 100, 40, "Back", font);
    Button threePlayerButton(375, 300, 100, 50, "3", font);
    Button fourPlayerButton(500, 300, 100, 50, "4", font);
    Button fivePlayerButton(625, 300, 100, 50, "5", font);

    Button buySharesButton(375, 500, 150, 50, "Buy Shares", font);
    Button sellSharesButton(375, 570, 150, 50, "Sell Shares", font);
    Button confirmBuyButton(700, 500, 150, 50, "CONFIRM", font);
    Button confirmSellButton(700, 570, 150, 50, "CONFIRM", font);
    Button skipTurnButton(375, 640, 150, 50, "Skip Turn", font);

    buySharesButton.setColor(sf::Color::Green, sf::Color::White);
    sellSharesButton.setColor(sf::Color::Red, sf::Color::White);

    // TextBox for number of shares input
    TextBox buySharesTextBox(550, 500, 100, 40);
    TextBox sellSharesTextBox(550, 570, 100, 40);

    buySharesTextBox.setTextColor(sf::Color::Green);
    sellSharesTextBox.setTextColor(sf::Color::Red);

    bool showBuySharesTextBox = false;
    bool showSellSharesTextBox = false;
    bool showNextButton = false;
    bool isGraphScreenActive = false;

    countdownButton.setOnCountdownFinish([&]() {
        isInGraphScreen = false;
        isInChoiceScreen = true;
        menuVisible = false;
        });

    std::vector<Player> players;


    auto createPlayerNameBoxes = [&](int numberOfPlayers) {
        playerNameBoxes.clear();
        players.clear(); // ล้างข้อมูลผู้เล่นก่อนสร้างใหม่

        float startY = 200;
        for (int i = 0; i < numberOfPlayers; ++i) {
            TextBox box(400, startY + i * 60, 200, 40);
            box.setFont(font);
            playerNameBoxes.push_back(box);
        }
        };

    auto createPlayersFromTextBoxes = [&]() {
        players.clear();
        for (const auto& box : playerNameBoxes) {
            std::string playerName = box.getText();
            if (playerName.empty()) {
                playerName = "Player " + std::to_string(players.size() + 1); // กำหนดชื่อเริ่มต้นหากไม่มีการใส่ชื่อ
            }
            players.emplace_back(playerName, 50000); // สร้าง Player object และใส่เงินเริ่มต้น
        }
        };


    int currentPlayer = 0;  // Add a variable to track the current player
    int turnCounter = 0;  // Track how many turns have been taken
    int roundCounter = 0; // Track the number of rounds (up to 5 rounds)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (isChoosingPlayers) {
                    if (threePlayerButton.isClicked(mousePos)) numberOfPlayers = 3;
                    else if (fourPlayerButton.isClicked(mousePos)) numberOfPlayers = 4;
                    else if (fivePlayerButton.isClicked(mousePos)) numberOfPlayers = 5;

                    if (numberOfPlayers > 0) {
                        createPlayerNameBoxes(numberOfPlayers);
                        isChoosingPlayers = false;
                        isEnteringNames = true;
                        menuVisible = false;  // Hide menu when entering names
                    }

                    if (backButton.isClicked(mousePos)) {
                        isChoosingPlayers = false;
                        menu.show();
                        menuVisible = true;  // Show menu when going back to the main menu
                    }

                }
                else if (isEnteringNames) {
                    if (nextButton.isClicked(mousePos)) {
                        createPlayersFromTextBoxes(); // สร้าง Player objects จาก TextBox
                        isEnteringNames = false;
                        isInStartScreen = true;
                        menuVisible = false;  // ซ่อนเมนูเมื่อเริ่มเกม
                    }
                    else if (backButton.isClicked(mousePos)) {
                        isEnteringNames = false;
                        isChoosingPlayers = true; // ย้อนกลับไปหน้ากำหนดจำนวนผู้เล่น
                        menuVisible = true;  // แสดงเมนูอีกครั้ง
                    }
                }
                else if (menu.IsBackClicked(window)) {
                    inTutorial = false;
                    isChoosingPlayers = false;
                    isEnteringNames = false;
                    isInStartScreen = false;
                    menu.show();  // Show main menu
                    menuVisible = true;  // Show menu when going back to the main menu
                }
                else if (!(isChoosingPlayers || isEnteringNames || inTutorial || isInStartScreen)) {
                    for (int i = 0; i < menu.GetItemCount(); ++i) {
                        if (menu.IsMouseOver(window, i)) {
                            switch (i) {
                            case 0:
                                isChoosingPlayers = true;
                                menu.hide();
                                menuVisible = false;  // Hide menu when going to player selection
                                break;
                            case 1:
                                inTutorial = true;
                                menu.hide();
                                menuVisible = false;  // Hide menu when going to tutorial
                                break;
                            case 2:
                                window.close();
                                break;
                            }
                        }
                    }
                }

                if (isInStartScreen && graphButton.isClicked(mousePos)) {
                    isInGraphScreen = true;
                    isInStartScreen = false; // Go to graph screen
                    menuVisible = false;  // Hide menu when in graph screen
                }

                if (isInGraphScreen && countdownButton.isClicked(mousePos)) {
                    isInGraphScreen = false;        // Exit graph screen
                    isGraphScreenActive = false;   // Change news state 
                    isInChoiceScreen = true;      // Go to choice screen
                    menuVisible = false;         // Hide menu when going to choice screen
                }

                if (isInGraphScreen) {
                    countdownButton.startCountdown(16);
                }

                if (countdownButton.isCountdownFinished()) {
                    isInGraphScreen = false;
                    isGraphScreenActive = false;
                    isInChoiceScreen = true;
                    menuVisible = false;
                }


                // Handle player choices for Buy, Sell, or Skip
                if (isInChoiceScreen) {
                    if (buySharesButton.isClicked(mousePos)) {
                        showBuySharesTextBox = true;
                        showSellSharesTextBox = false;
                    }
                    else if (sellSharesButton.isClicked(mousePos)) {
                        showSellSharesTextBox = true;
                        showBuySharesTextBox = false;
                    }
                    else if (confirmBuyButton.isClicked(mousePos) && showBuySharesTextBox) {
                        int amount = std::stoi(buySharesTextBox.getText());  // รับค่าจาก TextBox
                        double price = 100;  // ราคาหุ้นปัจจุบัน
                        players[currentPlayer].buyShares(amount, price);

                        showBuySharesTextBox = false;  // ปิด TextBox หลังจากซื้อเสร็จ
                        endTurn(currentPlayer, turnCounter, roundCounter, numberOfPlayers,
                            isInChoiceScreen, isInGraphScreen, isGraphScreenActive, countdownButton);
                    }
                    else if (confirmSellButton.isClicked(mousePos) && showSellSharesTextBox) {
                        int amount = std::stoi(sellSharesTextBox.getText());
                        double price = 100;
                        players[currentPlayer].sellShares(amount, price);

                        showSellSharesTextBox = false;  // ปิด TextBox หลังจากขายเสร็จ
                        endTurn(currentPlayer, turnCounter, roundCounter, numberOfPlayers,
                            isInChoiceScreen, isInGraphScreen, isGraphScreenActive, countdownButton);
                    }
                    else if (skipTurnButton.isClicked(mousePos)) {
                        endTurn(currentPlayer, turnCounter, roundCounter, numberOfPlayers,
                            isInChoiceScreen, isInGraphScreen, isGraphScreenActive, countdownButton);
                    }
                }
            }

            if (isEnteringNames) {
                for (auto& box : playerNameBoxes) {
                    box.handleEvent(event);
                }
            }

            // Handle TextBox events
            if (showBuySharesTextBox) {
                buySharesTextBox.handleEvent(event);
            }
            if (showSellSharesTextBox) {
                sellSharesTextBox.handleEvent(event);
            }
        }

        window.clear();
        if (menuVisible) {
            window.draw(background);
            menu.draw(window);  // Draw menu if menuVisible is true
        }
        else if (inTutorial) {
            window.draw(top);
        }
        else if (isChoosingPlayers) {
            window.draw(kornplays);
            threePlayerButton.draw(window);
            fourPlayerButton.draw(window);
            fivePlayerButton.draw(window);
            backButton.draw(window);
        }
        else if (isEnteringNames) {
            window.draw(kornplays);
            for (auto& box : playerNameBoxes) {
                box.draw(window);
            }
            nextButton.draw(window);
            backButton.draw(window);
        }
        else if (isInStartScreen) {
            window.draw(startja);
            drawPlayerTable(window, font, players,sf::Color::White);
            // แสดงปุ่มสำหรับไปยังหน้าต่อไป
            graphButton.draw(window);
        } else if (isInGraphScreen) {
            if (!isGraphScreenActive) { // ถ้าเพิ่งเข้าสู่หน้ากราฟ
                newsText.setString("Market Trend : " + news.getRandomNews()); // สุ่มข่าวใหม่
                stockGraph.resetGraph();
                isGraphScreenActive = true; // ตั้งค่าเพื่อไม่ให้เปลี่ยนอีกจนกว่าจะออกจากหน้ากราฟ
            }
            window.draw(kornplays);
            window.draw(graphArea);
            stockGraph.drawGraph(window, graphArea);
            countdownButton.draw(window);
            window.draw(newsText);
        }
        else if (isInChoiceScreen) {
            window.draw(choicenaka); // Draw choice screen
            buySharesButton.draw(window);
            sellSharesButton.draw(window);
            skipTurnButton.draw(window);
            confirmBuyButton.draw(window);
            confirmSellButton.draw(window);
            // Show the text boxes if needed
            if (showBuySharesTextBox) {
                buySharesTextBox.draw(window);
            }
            if (showSellSharesTextBox) {
                sellSharesTextBox.draw(window);
            }
            // แสดงผู้เล่นที่กำลังเล่น
            sf::Text turnText;
            turnText.setFont(font);
            turnText.setString("Turn of: " + players[currentPlayer].getName());
            turnText.setCharacterSize(30);
            turnText.setFillColor(sf::Color::Black);
            turnText.setPosition(700, 590); // Adjust position above the button
            window.draw(turnText);
            drawPlayerTable(window, font, players,sf::Color::Black);
        }
        window.display();
    }
    return 0;
}

void endTurn(int& currentPlayer, int& turnCounter, int& roundCounter,
    int numberOfPlayers, bool& isInChoiceScreen,
    bool& isInGraphScreen, bool& isGraphScreenActive,
    Button& countdownButton) {

    currentPlayer = (currentPlayer + 1) % numberOfPlayers;
    turnCounter++;

    if (turnCounter == numberOfPlayers) {
        std::cout << "All players have finished their turns.\n";
        countdownButton.startCountdown(16);
        turnCounter = 0;
        roundCounter++;

        if (roundCounter == 5) {
            std::cout << "5 rounds completed.\n";
            roundCounter = 0;
        }

        isInChoiceScreen = false;
        isInGraphScreen = true;
        isGraphScreenActive = false;
    }
}