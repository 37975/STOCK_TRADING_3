#include "Player.h"

Player::Player(const std::string& name, int startingMoney)
    : name(name), cash(startingMoney), shares(0), profit_loss(0.0), startingMoney(startingMoney) {
}

void Player::buyShares(int amount, double price) {
    double cost = amount * price;
    if (cash >= cost) {
        shares += amount;
        cash -= cost;
        recordTrade(-cost);  // บันทึกค่าใช้จ่ายในการซื้อหุ้น
    }
    else {
        std::cout << "Not enough cash to buy shares!\n";
    }
}

void Player::sellShares(int amount, double price) {
    if (shares >= amount) {
        double revenue = amount * price;
        shares -= amount;
        cash += revenue;
        recordTrade(revenue);  // บันทึกรายได้จากการขายหุ้น
    }
    else {
        std::cout << "Not enough shares to sell!\n";
    }
}

void Player::recordTrade(double amount) {
    trades.push_back(amount);
    profit_loss += amount;  // คำนวณกำไรหรือขาดทุน
}

void Player::displayInfo() const {
    std::cout << "Player: " << name << "\n";
    std::cout << "Cash: " << cash << "\n";
    std::cout << "Shares: " << shares << "\n";
    std::cout << "Profit/Loss: " << profit_loss << "\n";
}

std::string Player::getName() const { return name; }

int Player::getCash() const { return cash; }

int Player::getShares() const { return shares; }

int Player::getProfitLoss() const { return profit_loss; }

int Player::getStartingMoney() const { return startingMoney; }

const std::vector<int>& Player::getTrades() const { return trades; }
