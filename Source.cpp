#include "Header.h"

void ballGame::run()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Шарики\n"
        << "Вы вводите цифры, которые обозначают цвета шариков.\n"
        << "При появлении трёх и более подряд одинаковых чисел, программа удаляет их.\n" << endl;

    string ballStr;

    cout << "Введите общее количество шариков: ";


    int ballsNum = 0;

    while (!(getline(cin, ballStr)) || !inputValidator::validateBallCount(ballStr, ballsNum))
    {
        cout << endl;
    }

    list ballColors = getBallColors(ballsNum);
    int removedBalls = removeConsecutiveBalls(ballColors);

    cout << "Общее количество удалённых шариков: " << removedBalls << endl;
}

// подсчет данных вводимых пользователем
list ballGame::getBallColors(int ballCount) 
{
    list colorList;

    cout << "Введите " << ballCount << " целых чисел (цвета от 0 до 9): " << endl;
    for (int i = 0; i < ballCount; ++i)
    {
        int colorInput = 0;
        string colorBall;

        while (!(getline(cin,colorBall)) || !inputValidator::validateBallColor(colorBall, colorInput)) 
    
        {
            cout << "Ввведите корректное значение цвета шарика (целое число от 0 до 9): ";
            
        }

        colorList.addBall(colorInput);
    }
    return colorList;
}

//нахождение и удаление группы шаров
int ballGame::removeConsecutiveBalls(list& ballList) 
{
    if (ballList.isEmpty())
    {
        cout << "Нет шариков для обработки!" << endl;
        return 0;
    }

    int destroyed = 0;  // переменная для подсчёта удаленных шаров
    bool removed;   // переменная для проверки все ли цепочки удалены

    // цикл будет раюотать до тех пор, пока не будутудалены все цепочки
    do 
    {
        removed = false;
        ballNode* currentPos = ballList.getHead();
        ballNode* group = currentPos;
        ballNode* prev = nullptr;

       // если в списке ничего нет
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
                // если всстречается группа шаров больше 3, удаление
                if (consecutiveCount >= 3)
                {
                    removed = true;
                    destroyed += consecutiveCount;
                    ballNode* nextNode = currentPos;
                    ballList.eraseBall(groupStart, currentPos);
                    break;  // повтор итерации после удаления группы шаров
                }
                // подсчёт следующуй грппы шаров
                currentColor = currentPos -> color;
                consecutiveCount = 1;
                groupStart = currentPos;
            }
            currentPos = currentPos -> next;
        }

        // проверка последней группы шаров
        if (!removed && consecutiveCount >= 3) 
        {
            destroyed += consecutiveCount;
            ballList.eraseBall(groupStart, nullptr);
            removed = true;
        }

    } while (removed);

    return destroyed;
}

// проверка ввел ли пользователь строку
bool inputValidator::validateBallCount(const string& ballStr, int& ballsNum) 
{
    if (ballStr.empty())
    {
        cout << "Ошибка! Введите число.";
        return false;
    }
    if (ballStr[0] == '0')
    {
        cout << "Введите число больше 0" << endl;
        return false;
    }
    //проверка на длину вводимого числа, оно должно быть меньше 10^5
    if (ballStr.length() > 6)
    {
        cout << "Ошибка! Число слишком большое.";
        return false;
    }

    for (char ch : ballStr) 
    {
        if (!isdigit(ch)) 
        {
            cout << "Ошибка! Пожалуйста, введите только цифры без лишних символов.";
            return false;
        }
    }

    // проверка, что число не начинается с 0, если оно не является единственным
    if (ballStr[0] == '0' && ballStr.length() > 1) 
    {
        cout << "Ошибка! Число не может начинаться с 0.";
        return false;
    }

    try 
    {
        ballsNum = stoi(ballStr);
        return true;
    }
    catch (...)
    {
        cout << "Ошибка! Некорректное число.";
        return false;
    }
}

// проверка на ввод цыета шаров
bool inputValidator::validateBallColor(const string& colorBall, int& colorInput)
{
    if (colorBall.empty())
    {
        cout << "Ошибка! Введите число." << endl;
        return false;
    }

    //проверка на длину вводимого числа, оно должно быть меньше 10^5
    if (colorBall.length() > 1)
    {
        cout << "Ошибка! Введите число корректно." << endl;
        return false;
    }

    for (char c : colorBall)
    {
        if (!isdigit(c))
        {
            cout << "Ошибка! Пожалуйста, введите только цифры без лишних символов." << endl;
            return false;
        }
    }

    // проверка, что число не начинается с 0, если оно не является единственным
    if (colorBall[0] == '0' && colorBall.length() > 1)
    {
        cout << "Ошибка! Число не может начинаться с 0." << endl;
        return false;
    }

    try
    {
        colorInput = stoi(colorBall);
        return true;
    }
    catch (...)
    {
        cout << "Ошибка! Некорректное число." << endl;
        return false;
    }

    return true;
}