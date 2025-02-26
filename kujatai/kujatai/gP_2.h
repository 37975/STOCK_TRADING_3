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

    // �ѧ��ѹ����駤�Ҽš�з��ҡ����
    void setNewsEffect(int effect) {
        newsEffect = effect;
        float mean = float(newsEffect) * 0.5f;  // ��Ѻ��á�Ш�¢ͧ�š�з���� effect
        float stddev = 5.0f; // ���������û�ǹ���ͷ����������¹�ŧ�˭���
        distribution = normal_distribution<float>(mean, stddev);
    }

    // �ѧ��ѹ���ͻ�Ѻ�š�з��ͧ���Ƿ���ռŵ�͡�ҿ
    void applyNewsEffect(int effect) {
        setNewsEffect(effect);  // ��駤�Ҽš�з�����

        // ��û�Ѻ����¹�ҤҨҡ�š�з�
        resetGraph();  // ���絡�ҿ����
    }

    // ���絡�ҿ
    void resetGraph() {
        openPrices.clear();
        closePrices.clear();
        candles.clear();

        float basePrice = height / 2;
        float currentPrice = basePrice;

        // Ŵ�������ҧ�ͧ����¹ (Ŵ�ҡ 0.8f �� 0.5f)
        float candleWidth = (width / numPoints) * 0.5f;

        for (int i = 0; i < numPoints; i++) {
            // ���������ѹ�ǹ�ҡ��鹨ҡ�š�з�
            float priceChange = distribution(gen) * (abs(newsEffect) + 10.0f);  // �����������¹�ŧ�ҡ�š�з��ͧ����
            float open = currentPrice;
            float close = open + priceChange;

            // �ӡѴ�Ҥ��������ӡ��Ҥ�ҵ���ش�����٧�ش
            close = min(max(close, height * 0.1f), height * 0.9f);

            openPrices.push_back(open);
            closePrices.push_back(close);

            currentPrice = close;

            // ���ҧ����¹
            float candleHeight = abs(close - open);

            // ��������٧��鹨ҡ���
            if (candleHeight < 1.0f) candleHeight = 1.0f; // ������ҵ���ش�ͧ����¹����ӡ��� 1 pixel
            candleHeight *= 1.5f;  // ���������٧�ͧ����¹��鹨ҡ���

            sf::RectangleShape candle(sf::Vector2f(candleWidth, candleHeight));

            if (close > open) { // ����¹������
                candle.setPosition(i * (width / numPoints), height - open);
                candle.setFillColor(sf::Color::Green);
            }
            else { // ����¹��ᴧ
                candle.setPosition(i * (width / numPoints), height - close);
                candle.setFillColor(sf::Color::Red);
            }

            candles.push_back(candle);
        }
    }

    // �Ҵ��ҿŧ�˹�ҵ�ҧ
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
