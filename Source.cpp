#include "Header.h"

void ballGame::run()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

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

    list ballColors = getBallColors(ballsNum);
    int removedBalls = removeConsecutiveBalls(ballColors);

    cout << "����� ���������� �������� �������: " << removedBalls << endl;
}

// ������� ������ �������� �������������
list ballGame::getBallColors(int ballCount) 
{
    list colorList;

    cout << "������� " << ballCount << " ����� ����� (����� �� 0 �� 9): " << endl;
    for (int i = 0; i < ballCount; ++i)
    {
        int colorInput = 0;
        string colorBall;

        while (!(getline(cin,colorBall)) || !inputValidator::validateBallColor(colorBall, colorInput)) 
    
        {
            cout << "�������� ���������� �������� ����� ������ (����� ����� �� 0 �� 9): ";
            
        }

        colorList.addBall(colorInput);
    }
    return colorList;
}

//���������� � �������� ������ �����
int ballGame::removeConsecutiveBalls(list& ballList) 
{
    if (ballList.isEmpty())
    {
        cout << "��� ������� ��� ���������!" << endl;
        return 0;
    }

    int destroyed = 0;  // ���������� ��� �������� ��������� �����
    bool removed;   // ���������� ��� �������� ��� �� ������� �������

    // ���� ����� �������� �� ��� ���, ���� �� ������������ ��� �������
    do 
    {
        removed = false;
        ballNode* currentPos = ballList.getHead();
        ballNode* group = currentPos;
        ballNode* prev = nullptr;

       // ���� � ������ ������ ���
        if (currentPos == nullptr)
            break;

        int currentColor = currentPos -> color;
        int consecutiveCount = 1;
        auto groupStart = currentPos;
        currentPos = currentPos -> next;
        while (currentPos != nullptr)
        {
            if (currentPos -> color == currentColor)
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
                    ballNode* nextNode = currentPos;
                    ballList.eraseBall(groupStart, currentPos);
                    break;  // ������ �������� ����� �������� ������ �����
                }
                // ������� ��������� ����� �����
                currentColor = currentPos -> color;
                consecutiveCount = 1;
                groupStart = currentPos;
            }
            currentPos = currentPos -> next;
        }

        // �������� ��������� ������ �����
        if (!removed && consecutiveCount >= 3) 
        {
            destroyed += consecutiveCount;
            ballList.eraseBall(groupStart, nullptr);
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
    if (ballStr[0] == '0')
    {
        cout << "������� ����� ������ 0" << endl;
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