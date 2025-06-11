#pragma once

#include <iostream>
#include <list>
#include <string>
#include <limits>

using namespace std; 

// ����� ��� �������� ������������ ������
class InputValidator {
public:
    // �������� ����� �� ������� ����� �����
    static bool validateBallCount(const string& rawInput, int& result);

    //�������� ����� �� ������� ����� �������
    static bool validateBallColor(int color);
};

// ����� ��� ���������� ����� ����
class BallGame {
public:
    
    void run();

private:
    // ������� ������ � ������� �� ���������� � ����
    list<int> getBallColors(int& ballCount);

    // �������� �� ������������� � �������� ������� �� 3 � ����� �������
    int removeConsecutiveBalls(list<int>& ballList);
};