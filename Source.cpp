#include "Header.h"

void ballGame::run()
{
    cout << "������\n"
        << "�� ������� �����, ������� ���������� ����� �������.\n"
        << "��� ��������� ��� � ����� ������ ���������� �����, ��������� ������� ��.\n" << endl;

    string ballStr;

    cout << "������� ����� ���������� �������: ";


    int ballsNum = 0;

    while (!(getline(cin, ballStr)) || !inputValidator::validateBallCount(ballStr, ballsNum))
    {
        cout << endl;
    }

    list<int> ballColors = getBallColors(ballsNum);
    int removedBalls = removeConsecutiveBalls(ballColors);

    cout << "����� ���������� �������� �������: " << removedBalls << endl;
}

// ������� ������ �������� �������������
list<int> ballGame::getBallColors(int& ballCount) 
{
    list<int> colorList;

    cout << "������� " << ballCount << " ����� ����� (����� �� 0 �� 9): " << endl;
    for (int i = 0; i < ballCount; ++i)
    {
        int colorInput = 0;
        string colorBall;

        while (!(getline(cin,colorBall)) || !inputValidator::validateBallColor(colorBall, colorInput)) 
    
        {
            cout << "�������� ���������� �������� ����� ������ (����� ����� �� 0 �� 9): ";
            
        }

        colorList.push_back(colorInput);
    }
    return colorList;
}

//���������� � �������� ������ �����
int ballGame::removeConsecutiveBalls(list<int>& ballList) 
{
    if (ballList.empty())
    {
        cout << "��� ������� ��� ���������!" << endl;
        return 0;
    }

    int destroyed = 0; // ���������� ��� �������� ��������� �����
    bool removed;  // ���������� ��� �������� ��� �� ������� �������

    // ���� ����� �������� �� ��� ���, ���� �� ������������ ��� �������
    do 
    {
        removed = false;
        auto currentPos = ballList.begin();

       // ���� � ������ ������ ���
        if (currentPos == ballList.end())
            break;

        int currentColor = *currentPos;
        int consecutiveCount = 1;
        auto groupStart = currentPos;
        ++currentPos;
        while (currentPos != ballList.end())
        {
            if (*currentPos == currentColor)
            {
                consecutiveCount++;
            }
            else
            {
                // ���� ������������ ������ ����� ������ 3, ��������
                if (consecutiveCount >= 3)
                {
                    removed = true;
                    destroyed += consecutiveCount;
                    ballList.erase(groupStart, currentPos);
                    break;  // ������ �������� ����� �������� ������ �����
                }
                // ������� ��������� ����� �����
                currentColor = *currentPos;
                consecutiveCount = 1;
                groupStart = currentPos;
            }
            ++currentPos;
        }

        // �������� ��������� ������ �����
        if (!removed && consecutiveCount >= 3) 
        {
            destroyed += consecutiveCount;
            ballList.erase(groupStart, ballList.end());
            removed = true;
        }

    } while (removed);

    return destroyed;
}

// �������� ���� �� ������������ ������
bool inputValidator::validateBallCount(const string& ballStr, int& ballsNum) 
{
    if (ballStr.empty())
    {
        cout << "������! ������� �����.";
        return false;
    }

    //�������� �� ����� ��������� �����, ��� ������ ���� ������ 10^5
    if (ballStr.length() > 6)
    {
        cout << "������! ����� ������� �������.";
        return false;
    }

    for (char ch : ballStr) 
    {
        if (!isdigit(ch)) 
        {
            cout << "������! ����������, ������� ������ ����� ��� ������ ��������.";
            return false;
        }
    }

    // ��������, ��� ����� �� ���������� � 0, ���� ��� �� �������� ������������
    if (ballStr[0] == '0' && ballStr.length() > 1) 
    {
        cout << "������! ����� �� ����� ���������� � 0.";
        return false;
    }

    try 
    {
        ballsNum = stoi(ballStr);
        return true;
    }
    catch (...)
    {
        cout << "������! ������������ �����.";
        return false;
    }
}

// �������� �� ���� ����� �����
bool inputValidator::validateBallColor(const string& colorBall, int& colorInput)
{
    if (colorBall.empty())
    {
        cout << "������! ������� �����." << endl;
        return false;
    }

    //�������� �� ����� ��������� �����, ��� ������ ���� ������ 10^5
    if (colorBall.length() > 1)
    {
        cout << "������! ������� ����� ���������." << endl;
        return false;
    }

    for (char c : colorBall)
    {
        if (!isdigit(c))
        {
            cout << "������! ����������, ������� ������ ����� ��� ������ ��������." << endl;
            return false;
        }
    }

    // ��������, ��� ����� �� ���������� � 0, ���� ��� �� �������� ������������
    if (colorBall[0] == '0' && colorBall.length() > 1)
    {
        cout << "������! ����� �� ����� ���������� � 0." << endl;
        return false;
    }

    try
    {
        colorInput = stoi(colorBall);
        return true;
    }
    catch (...)
    {
        cout << "������! ������������ �����." << endl;
        return false;
    }

    return true;
}