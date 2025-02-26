#ifndef PLAYER_H 
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

class Player {
public:
    Player(const std::string& name, int startingMoney);

    void buyShares(int amount, double price);
    void sellShares(int amount, double price);
    void recordTrade(double amount);
    void displayInfo() const;

    std::string getName() const;
    int getCash() const;
    int getShares() const;
    int getProfitLoss() const;
    int getStartingMoney() const;
    const std::vector<int>& getTrades() const;

private:
    std::string name;
    int cash;
    int shares;
    int profit_loss;
    int startingMoney;
    std::vector<int> trades;
};

#endif // PLAYER_H
