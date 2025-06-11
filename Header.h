#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Windows.h"
#include <limits>

using namespace std; 

// ����� ��� �������� ������������ ������
class inputValidator
{
public:
    // �������� ����� �� ������� ����� �����
    static bool validateBallCount(const string& rawInput, int& result);

    //�������� ����� �� ������� ����� �������
    static bool validateBallColor(const string& colorBall, int& colorInput);
};

// ����� ��� ���������� ����� ����
class ballGame 
{
public:
    
    void run();

private:
    // ������� ������ � ������� �� ���������� � ����
    list<int> getBallColors(int& ballCount);

    // �������� �� ������������� � �������� ������� �� 3 � ����� �������
    int removeConsecutiveBalls(list<int>& ballList);
};