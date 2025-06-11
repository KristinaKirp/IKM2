#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Windows.h"
#include <limits>

using namespace std; 

// класс для проверки корректности данных
class inputValidator
{
public:
    // проверка верно ли введено число щаров
    static bool validateBallCount(const string& rawInput, int& result);

    //проверка верно ли введено число шариков
    static bool validateBallColor(const string& colorBall, int& colorInput);
};

// класс для реализации самой игры
class ballGame 
{
public:
    
    void run();

private:
    // подсчет данных о шариках их количесвто и цвет
    list<int> getBallColors(int& ballCount);

    // проверка на существование и удаление цепочки из 3 и более шариков
    int removeConsecutiveBalls(list<int>& ballList);
};