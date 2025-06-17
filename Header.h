#pragma once

#include <iostream>
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

struct ballNode
{
    int color;          // Цвет шарика
    ballNode* next;     // Указатель на следующий узел

    ballNode(int col) : color(col), next(nullptr) {}
};

class list 
{
private:
    ballNode* head;     // Указатель на начало списка
    ballNode* tail;     // Указатель на конец списка (для оптимизации добавления)
    int size;          // Количество элементов в списке

public:
    // Конструктор
    list() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор (очистка памяти)
    ~list()
    {
        clear();
    }

    // Добавление шарика в конец списка
    void addBall(int color)
    {
        ballNode* newNode = new ballNode(color);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Очистка списка
    void clear() 
    {
        ballNode* current = head;
        while (current != nullptr) 
        {
            ballNode* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Получение количества шариков
    int getSize() const 
    {
        return size;
    }

    // Проверка на пустоту
    bool isEmpty() const
    {
        return size == 0;
    } 
    // возвращаемся в начало списка  
    ballNode* getHead() const
    {
        return head;
    }

    void eraseBall(ballNode* start, ballNode* end)
    {
        if (!start || !head) return;

        ballNode* current = head;
        ballNode* prev = nullptr;
        ballNode* nodeToDelete = nullptr;
        int count = 0;

        // Находим узел перед start
        while (current != start && current != nullptr) {
            prev = current;
            current = current->next;
        }

        if (current != start) return; // start не найден

        // Удаляем узлы от start до end
        while (current != end && current != nullptr) {
            nodeToDelete = current;
            current = current->next;
            delete nodeToDelete;
            count++;
        }
        if (prev) {
            prev->next = current; // Связываем предыдущий узел с end
        }
        else {
            head = current; // Если удаляли с начала списка
        }

        // Обновляем tail, если удалили конец
        if (current == nullptr) {
            tail = prev;
        }

        size -= count;
    }   

};


// класс для реализации самой игры
class ballGame
{
public:

    void run();

private:
    // подсчет данных о шариках их количесвто и цвет
    list getBallColors(int ballCount);

    // проверка на существование и удаление цепочки из 3 и более шариков
    int removeConsecutiveBalls(list& ballList);
};