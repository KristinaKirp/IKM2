#pragma once

#include <iostream>
#include <list>
#include <string>
#include <limits>

using namespace std; 

// класс для проверки корректности данных
class InputValidator {
public:
    // проверка верно ли введено число щаров
    static bool validateBallCount(const string& rawInput, int& result);

    //проверка верно ли введено число шариков
    static bool validateBallColor(int color);
};

// класс для реализации самой игры
class BallGame {
public:
    
    void run();

private:
    // подсчет данных о шариках их количесвто и цвет
    list<int> getBallColors(int& ballCount);

    // проверка на существование и удаление цепочки из 3 и более шариков
    int removeConsecutiveBalls(list<int>& ballList);
};