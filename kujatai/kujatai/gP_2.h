#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

class StockGraph {
private:
    float width;
    float height;
    const int numPoints = 50;
    int newsEffect;
    vector<float> openPrices, closePrices;
    random_device rd;
    mt19937 gen;
    normal_distribution<float> distribution;
    vector<sf::RectangleShape> candles;

public:
    StockGraph(float w, float h) :
        width(w),
        height(h),
        newsEffect(0),
        gen(rd()),
        distribution(0.0f, 1.0f) {
        resetGraph();
    }

    // ฟังก์ชันที่ตั้งค่าผลกระทบจากข่าว
    void setNewsEffect(int effect) {
        newsEffect = effect;
        float mean = float(newsEffect) * 0.5f;  // ปรับการกระจายของผลกระทบตาม effect
        float stddev = 5.0f; // เพิ่มความแปรปรวนเพื่อทำให้การเปลี่ยนแปลงใหญ่ขึ้น
        distribution = normal_distribution<float>(mean, stddev);
    }

    // ฟังก์ชันเพื่อปรับผลกระทบของข่าวที่มีผลต่อกราฟ
    void applyNewsEffect(int effect) {
        setNewsEffect(effect);  // ตั้งค่าผลกระทบใหม่

        // การปรับเปลี่ยนราคาจากผลกระทบ
        resetGraph();  // รีเซ็ตกราฟใหม่
    }

    // รีเซ็ตกราฟ
    void resetGraph() {
        openPrices.clear();
        closePrices.clear();
        candles.clear();

        float basePrice = height / 2;
        float currentPrice = basePrice;

        // ลดความกว้างของแท่งเทียน (ลดจาก 0.8f เป็น 0.5f)
        float candleWidth = (width / numPoints) * 0.5f;

        for (int i = 0; i < numPoints; i++) {
            // เพิ่มความผันผวนมากขึ้นจากผลกระทบ
            float priceChange = distribution(gen) * (abs(newsEffect) + 10.0f);  // เพิ่มการเปลี่ยนแปลงจากผลกระทบของข่าว
            float open = currentPrice;
            float close = open + priceChange;

            // จำกัดราคาให้ไม่ต่ำกว่าค่าต่ำสุดหรือสูงสุด
            close = min(max(close, height * 0.1f), height * 0.9f);

            openPrices.push_back(open);
            closePrices.push_back(close);

            currentPrice = close;

            // สร้างแท่งเทียน
            float candleHeight = abs(close - open);

            // เพิ่มค่าสูงขึ้นจากเดิม
            if (candleHeight < 1.0f) candleHeight = 1.0f; // ทำให้ค่าต่ำสุดของแท่งเทียนไม่ต่ำกว่า 1 pixel
            candleHeight *= 1.5f;  // เพิ่มความสูงของแท่งเทียนขึ้นจากเดิม

            sf::RectangleShape candle(sf::Vector2f(candleWidth, candleHeight));

            if (close > open) { // แท่งเทียนสีเขียว
                candle.setPosition(i * (width / numPoints), height - open);
                candle.setFillColor(sf::Color::Green);
            }
            else { // แท่งเทียนสีแดง
                candle.setPosition(i * (width / numPoints), height - close);
                candle.setFillColor(sf::Color::Red);
            }

            candles.push_back(candle);
        }
    }

    // วาดกราฟลงในหน้าต่าง
    void drawGraph(sf::RenderWindow& window, const sf::RectangleShape& chartArea) {
        sf::View currentView = window.getView();

        sf::View graphView;
        sf::Vector2f chartPos = chartArea.getPosition();
        sf::Vector2f chartSize = chartArea.getSize();

        graphView.reset(sf::FloatRect(0, 0, width, height));
        graphView.setViewport(sf::FloatRect(
            chartPos.x / window.getSize().x,
            chartPos.y / window.getSize().y,
            chartSize.x / window.getSize().x,
            chartSize.y / window.getSize().y
        ));

        window.setView(graphView);

        for (const auto& candle : candles) {
            window.draw(candle);
        }

        window.setView(currentView);
    }
};
